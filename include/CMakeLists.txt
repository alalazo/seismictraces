SET( 
  SeismicTraces_includes
  SeismicTrace-inl.h
  SegyFile.h
)

SET( 
  SeismicTraces_impl_includes
  impl/SegyFile-constants.h
  impl/SegyFile-TextualFileHeader.h
  impl/SegyFile-BinaryFileHeader.h
  impl/SegyFile-TraceHeader.h
)

INSTALL( 
  FILES ${SeismicTraces_includes}
  DESTINATION include
)

INSTALL(
  FILES ${SeismicTraces_impl_includes}
  DESTINATION include/impl
)