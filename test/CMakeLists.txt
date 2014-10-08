FIND_PACKAGE( Boost 1.53 REQUIRED COMPONENTS unit_test_framework )

SET(
  SeismicTraces_available_tests_sources
  TextualFileHeader-tests.cpp
)

##########
## Dynamic library : collection of tests
ADD_LIBRARY( seismic_traces_test ${SeismicTraces_available_tests_sources})
TARGET_COMPILE_DEFINITIONS(
  seismic_traces_test
  PUBLIC BOOST_TEST_DYN_LINK
)
TARGET_LINK_LIBRARIES(
  seismic_traces_test
  PUBLIC
  SeismicTraces
  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)
##########

##########
## Executable : dumb runner that triggers the tests that are dynamically linked
ADD_EXECUTABLE( test_seismic_traces.x test_main.cpp )
TARGET_LINK_LIBRARIES(
  test_seismic_traces.x
  seismic_traces_test
)
##########
ADD_TEST(run_unit_test test_seismic_traces.x )
