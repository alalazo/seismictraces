SET( 
  example_sources 
  example02.cpp
  example03.cpp
  example04.cpp
  example05.cpp
  example06.cpp
)

SET( EXAMPLE_MACRO_IN  ${CMAKE_CURRENT_SOURCE_DIR}/example_macro.cmake.h )
SET( EXAMPLE_MACRO_OUT ${CMAKE_CURRENT_SOURCE_DIR}/example_macro.h       )
SET( DATA_FOLDER ${PROJECT_SOURCE_DIR}/data )

CONFIGURE_FILE( ${EXAMPLE_MACRO_IN} ${EXAMPLE_MACRO_OUT} )
INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR} )

FOREACH( source ${example_sources} )
  GET_FILENAME_COMPONENT( example_name ${source} NAME_WE )
  ADD_EXECUTABLE( ${example_name} ${source} )
  TARGET_LINK_LIBRARIES( ${example_name} SeismicTraces )
ENDFOREACH()
