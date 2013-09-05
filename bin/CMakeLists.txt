SET( 
  segyDump_sources
  segyDump.cpp
)

ADD_EXECUTABLE( segyDump ${segyDump_sources} )

TARGET_LINK_LIBRARIES( segyDump SeismicTraces )

INSTALL(
  TARGETS segyDump
  DESTINATION bin
)