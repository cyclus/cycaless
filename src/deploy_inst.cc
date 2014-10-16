// Implements the DeployInst class
#include "deploy_inst.h"

namespace cycaless {

DeployInst::DeployInst(cyclus::Context* ctx) : cyclus::Institution(ctx) {}

DeployInst::~DeployInst() {}

#pragma cyclus def clone cycaless::DeployInst

std::string DeployInst::schema() {
    return
        "<element name=\"buildorder\">            \n"
        "<oneOrMore>                               \n"
        "  <element name=\"prototype\">           \n"
        "    <data type=\"string\"/>              \n"
        "  </element>                             \n"
        "  <element name=\"number\">              \n"
        "    <data type=\"nonNegativeInteger\"/>  \n"
        "  </element>                             \n"
        "  <element name=\"date\">                \n"
        "    <data type=\"nonNegativeInteger\"/>  \n"
        "  </element>                             \n"
        "</oneOrMore>                              \n"
        "</element>                               \n";
}

void DeployInst::InfileToDb(cyclus::InfileTree* qe, cyclus::DbInit di) {
  cyclus::Institution::InfileToDb(qe, di);
  qe = qe->SubTree("config/*");
  cyclus::InfileTree* orders = qe->SubTree("buildorder");
  int nOrders = qe->NMatches("prototype");
  for (int i = 0; i < nOrders; i++) {
    int n = cyclus::Query<int>(orders, "number", i);
    for (int j = 0; j < n; ++j) {
      di.NewDatum("BuildOrder")
          ->AddVal("prototype", orders->GetString("prototype", i))
          ->AddVal("date", cyclus::Query<int>(orders, "date", i))
          ->Record();
    }
  }
}

void DeployInst::InitFrom(cyclus::QueryableBackend* b) {
  cyclus::Institution::InitFrom(b);
  cyclus::QueryResult qr = b->Query("BuildOrder", NULL);
  for (int i = 0; i < qr.rows.size(); i++) {
    std::string proto = qr.GetVal<std::string>("prototype", i);
    int t = qr.GetVal<int>("date", i);
    build_sched_[t].push_back(proto);
  }
}

void DeployInst::InitFrom(DeployInst* m) {
  cyclus::Institution::InitFrom(m);
  build_sched_ = m->build_sched_;
}

void DeployInst::Snapshot(cyclus::DbInit di) {
  cyclus::Institution::Snapshot(di);

  BuildSched::iterator it;
  for (it = build_sched_.begin(); it != build_sched_.end(); ++it) {
    int t = it->first;
    std::vector<std::string> protos = it->second;
    for (int i = 0; i < protos.size(); ++i) {
      di.NewDatum("BuildOrder")
          ->AddVal("prototype", protos[i])
          ->AddVal("date", t)
          ->Record();
    }
  }
}

void DeployInst::Build(cyclus::Agent* parent) {
  cyclus::Institution::Build(parent);
  BuildSched::iterator it;
  for (it = build_sched_.begin(); it != build_sched_.end(); ++it) {
    int t = it->first;
    std::vector<std::string> protos = it->second;
    for (int i = 0; i < protos.size(); ++i) {
      context()->SchedBuild(this, protos[i], t);
    }
  }
}

extern "C" cyclus::Agent* ConstructDeployInst(cyclus::Context* ctx) {
  return new DeployInst(ctx);
}

}  // namespace cycaless
