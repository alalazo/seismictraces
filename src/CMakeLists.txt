SET( 
  SeismicTraces_sources
  SegyFile.cpp
  impl/SegyFile-TextualFileHeader.cpp
)

ADD_LIBRARY( SeismicTraces ${SeismicTraces_sources} )
