SET( 
  SeismicTraces_sources
  SegyFile.cpp
  impl/SegyFile-TextualFileHeader.cpp
  impl/SegyFile-BinaryFileHeader.cpp
)

ADD_LIBRARY( SeismicTraces ${SeismicTraces_sources} )
