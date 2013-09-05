SET( 
  SeismicTraces_sources
  SegyFile.cpp
  Conversion.cpp
  impl/SegyFile-TextualFileHeader.cpp
  impl/SegyFile-BinaryFileHeader.cpp
  impl/SegyFile-TraceHeader.cpp
  impl/rev0/SegyFile-BinaryFileHeader-Rev0.cpp
)

ADD_LIBRARY( SeismicTraces ${SeismicTraces_sources} )

INSTALL(
  TARGETS SeismicTraces
  DESTINATION lib
)