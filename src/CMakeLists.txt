# ------------------- Add all Concrete Agents ----------------------------

USE_CYCLUS("cycaless" "batch_reactor")

USE_CYCLUS("cycaless" "enrichment_facility")

#USE_CYCLUS("cycaless" "inpro_reactor")

USE_CYCLUS("cycaless" "sink")

USE_CYCLUS("cycaless" "source")

USE_CYCLUS("cycaless" "deploy_inst")

USE_CYCLUS("cycaless" "manager_inst")

USE_CYCLUS("cycaless" "growth_region")

INSTALL_CYCLUS_MODULE("cycaless" "" "NONE")

SET(TestSource ${cycaless_TEST_CC} PARENT_SCOPE)

# install header files
FILE(GLOB h_files "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
INSTALL(FILES ${h_files} DESTINATION include/cycaless COMPONENT cycaless)
