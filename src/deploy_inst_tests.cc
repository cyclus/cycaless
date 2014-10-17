#include <gtest/gtest.h>

#include "context.h"
#include "deploy_inst.h"
#include "institution_tests.h"
#include "agent_tests.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
cyclus::Agent* DeployInstitutionConstructor(cyclus::Context* ctx) {
  return new cycaless::DeployInst(ctx);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
class DeployInstTest : public ::testing::Test {
 protected:
  virtual void SetUp() {}

  virtual void TearDown() {}
};

// required to get functionality in cyclus agent unit tests library
#ifndef CYCLUS_AGENT_TESTS_CONNECTED
int ConnectAgentTests();
static int cyclus_agent_tests_connected = ConnectAgentTests();
#define CYCLUS_AGENT_TESTS_CONNECTED cyclus_agent_tests_connected
#endif  // CYCLUS_AGENT_TESTS_CONNECTED

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
INSTANTIATE_TEST_CASE_P(DeployInst, InstitutionTests,
                        Values(&DeployInstitutionConstructor));
INSTANTIATE_TEST_CASE_P(DeployInst, AgentTests,
                        Values(&DeployInstitutionConstructor));
