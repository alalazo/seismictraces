SET( 
  example_sources 
  example01.cpp
  example02.cpp
  example03.cpp
)

FOREACH( source ${example_sources} )
  GET_FILENAME_COMPONENT( example_name ${source} NAME_WE )
  ADD_EXECUTABLE( ${example_name} ${source} )
  TARGET_LINK_LIBRARIES( ${example_name} SeismicTraces )
ENDFOREACH()