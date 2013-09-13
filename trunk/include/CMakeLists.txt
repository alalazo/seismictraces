SET( 
  SeismicTraces_includes
  SeismicTrace-inl.h
  SegyFile.h
  Conversion.h
)

SET( 
  SeismicTraces_impl_includes
  impl/utilities-inl.h
  impl/metafunctions-inl.h
  impl/ObjectFactory-inl.h
  impl/GenericByteStream-inl.h
  impl/SegyFile-constants.h
  impl/SegyFile-TextualFileHeader.h
  impl/SegyFile-BinaryFileHeader.h
  impl/SegyFile-TraceHeaderInterface.h
  impl/SegyFile-TraceHeader.h
)

SET( 
  SeismicTraces_rev0_includes
  impl/rev0/SegyFile-Fields-Rev0.h
  impl/rev0/SegyFile-BinaryFileHeader-Rev0.h
  impl/rev0/SegyFile-TraceHeader-Rev0.h
)

SET( 
  SeismicTraces_rev1_includes
  impl/rev1/SegyFile-Fields-Rev1.h
  impl/rev1/SegyFile-BinaryFileHeader-Rev1.h
  impl/rev1/SegyFile-TraceHeader-Rev1.h
)

INSTALL( 
  FILES ${SeismicTraces_includes}
  DESTINATION include
)

INSTALL(
  FILES ${SeismicTraces_impl_includes} 
  DESTINATION include/impl
)

INSTALL(
  FILES ${SeismicTraces_rev0_includes} 
  DESTINATION include/impl/rev0
)

INSTALL(
  FILES ${SeismicTraces_rev1_includes} 
  DESTINATION include/impl/rev1
)