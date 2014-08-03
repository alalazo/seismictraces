OPTION(ENABLE_TESTING "Enable the build of unit tests, add 'test' target to Makefile" OFF)

IF( ENABLE_TESTING )
  enable_testing()
  ## The Google testing framework is used for unit tests
  FIND_PACKAGE( Threads )
  FIND_PACKAGE( GTest )
  SET(
    SeismicTraces_available_tests_sources
    SeismicTrace-tests.cpp
    TextualFileHeader-tests.cpp
  )

  FOREACH( test_source ${SeismicTraces_available_tests_sources} )
    GET_FILENAME_COMPONENT( test_name ${test_source} NAME_WE )
    ADD_EXECUTABLE( ${test_name} ${test_source} )
    TARGET_LINK_LIBRARIES( ${test_name} SeismicTraces ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} )
    ADD_TEST( "${test_name}-target"  ${test_name})
  ENDFOREACH()
ENDIF()

