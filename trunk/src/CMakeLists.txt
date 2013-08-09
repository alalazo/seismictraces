SET( 
  SeismicTraces_sources
  SegyFile.cpp
  impl/SegyFile-TextualFileHeader.cpp
  impl/SegyFile-BinaryFileHeader.cpp
  impl/SegyFile-TraceHeader.cpp
)

ADD_LIBRARY( SeismicTraces ${SeismicTraces_sources} )

INSTALL(
  TARGETS SeismicTraces
  DESTINATION lib
)