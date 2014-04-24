SET( 
  SeismicTraces_sources
  SegyFile.cpp
  Conversion.cpp
  impl/SegyFile-TextualFileHeader.cpp
  impl/SegyFile-TraceHeader.cpp
  impl/rev0/SegyFile-BinaryFileHeader-Rev0.cpp
  impl/rev0/SegyFile-Fields-Rev0.cpp
  impl/rev0/SegyFile-TraceHeader-Rev0.cpp
  impl/rev1/SegyFile-BinaryFileHeader-Rev1.cpp
  impl/rev1/SegyFile-Fields-Rev1.cpp
  impl/rev1/SegyFile-TraceHeader-Rev1.cpp  
)

ADD_LIBRARY( SeismicTraces ${SeismicTraces_sources} )

INSTALL(
  TARGETS SeismicTraces
  DESTINATION lib
)