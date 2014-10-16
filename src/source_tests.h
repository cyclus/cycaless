#ifndef CYCALESS_SRC_SOURCE_TESTS_H_
#define CYCALESS_SRC_SOURCE_TESTS_H_
#include "source.h"

#include <gtest/gtest.h>

#include <boost/shared_ptr.hpp>

#include "agent_tests.h"
#include "context.h"
#include "exchange_context.h"
#include "facility_tests.h"
#include "material.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
class SourceTest : public ::testing::Test {
 public:
  cyclus::TestContext tc;
  TestFacility* trader;
  cycaless::Source* src_facility;
  std::string commod, recipe_name;
  double capacity;
  cyclus::Composition::Ptr recipe;

  virtual void SetUp();
  virtual void TearDown();
  void InitParameters();
  void SetUpSource();

  boost::shared_ptr< cyclus::ExchangeContext<cyclus::Material> >
      GetContext(int nreqs, std::string commodity);
};

#endif  // CYCALESS_SRC_SOURCE_TESTS_H_
