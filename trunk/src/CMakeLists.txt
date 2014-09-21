SET( 
  SeismicTraces_sources
  SegyFile.cpp
  impl/SegyFile-TextualFileHeader.cpp
  impl/SegyFileLazyWriter.cpp
  impl/utilities-inl.cpp
  impl/indexer/InMemoryIndexer.cpp
  impl/indexer/InFileIndexer.cpp
  impl/rev0/SegyFile-BinaryFileHeader-Rev0.cpp
  impl/rev0/SegyFile-Fields-Rev0.cpp
  impl/rev0/SegyFile-TraceHeader-Rev0.cpp
  impl/rev1/SegyFile-BinaryFileHeader-Rev1.cpp
  impl/rev1/SegyFile-Fields-Rev1.cpp
  impl/rev1/SegyFile-TraceHeader-Rev1.cpp  
)

ADD_LIBRARY( SeismicTraces ${SeismicTraces_sources} ${Doxygen_DEPENDENCIES} )

TARGET_INCLUDE_DIRECTORIES(
  SeismicTraces
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

TARGET_INCLUDE_DIRECTORIES(
  SeismicTraces SYSTEM
  PUBLIC ${Boost_INCLUDE_DIRS}
)

TARGET_LINK_LIBRARIES(
  SeismicTraces
  ${Boost_LIBRARIES}
)

INSTALL(
  TARGETS SeismicTraces
  EXPORT Seismic
  DESTINATION lib
)
