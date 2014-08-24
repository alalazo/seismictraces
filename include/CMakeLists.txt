SET( 
  SeismicTraces_includes
  ${CMAKE_CURRENT_SOURCE_DIR}/SegyFile.h
)

SET( 
  SeismicTraces_impl_includes
  ${CMAKE_CURRENT_SOURCE_DIR}/impl/utilities-inl.h
  ${CMAKE_CURRENT_SOURCE_DIR}/impl/metafunctions-inl.h
  ${CMAKE_CURRENT_SOURCE_DIR}/impl/ObjectFactory-inl.h
  ${CMAKE_CURRENT_SOURCE_DIR}/impl/GenericByteStream-inl.h
  ${CMAKE_CURRENT_SOURCE_DIR}/impl/SegyFile-constants.h
  ${CMAKE_CURRENT_SOURCE_DIR}/impl/SegyFile-TextualFileHeader.h
  ${CMAKE_CURRENT_SOURCE_DIR}/impl/SegyFile-BinaryFileHeader.h
  ${CMAKE_CURRENT_SOURCE_DIR}/impl/SegyFile-TraceHeader.h
  ${CMAKE_CURRENT_SOURCE_DIR}/impl/SegyFile-Trace.h
  ${CMAKE_CURRENT_SOURCE_DIR}/impl/SegyFileIndexer.h
  ${CMAKE_CURRENT_SOURCE_DIR}/impl/SegyFileLazyWriter.h
)

SET( 
  SeismicTraces_indexer_includes
  ${CMAKE_CURRENT_SOURCE_DIR}/impl/indexer/InMemoryIndexer.h
)


SET( 
  SeismicTraces_rev0_includes
  ${CMAKE_CURRENT_SOURCE_DIR}/impl/rev0/SegyFile-Fields-Rev0.h
  ${CMAKE_CURRENT_SOURCE_DIR}/impl/rev0/SegyFile-BinaryFileHeader-Rev0.h
  ${CMAKE_CURRENT_SOURCE_DIR}/impl/rev0/SegyFile-TraceHeader-Rev0.h
)

SET( 
  SeismicTraces_rev1_includes
  ${CMAKE_CURRENT_SOURCE_DIR}/impl/rev1/SegyFile-Fields-Rev1.h
  ${CMAKE_CURRENT_SOURCE_DIR}/impl/rev1/SegyFile-BinaryFileHeader-Rev1.h
  ${CMAKE_CURRENT_SOURCE_DIR}/impl/rev1/SegyFile-TraceHeader-Rev1.h
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

SET(
  Doxygen_DEPENDENCIES
  ${SeismicTraces_includes}
  ${SeismicTraces_impl_includes} 
  ${SeismicTraces_rev0_includes}
  ${SeismicTraces_rev1_includes} 
  ${SeismicTraces_indexer_includes}  
  PARENT_SCOPE
)
