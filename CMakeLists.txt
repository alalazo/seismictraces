CMAKE_MINIMUM_REQUIRED( VERSION 3.0.0 )

PROJECT( SeismicTraces C CXX )
SET( SeismicTraces_VERSION_MAJOR 1 )
SET( SeismicTraces_VERSION_MINOR 0 )
SET( SeismicTraces_VERSION "${SeismicTraces_VERSION_MAJOR}.${SeismicTraces_VERSION_MINOR}" )

SET(CMAKE_WARN_DEPRECATED TRUE)
###################
## Build options ##
###################

OPTION(BUILD_SHARED_LIBS "Create shared libraries instead of static ones (default OFF)" ON)
OPTION(LARGE_FILE_SUPPORT "Enable support for large files on 32-bit platforms" ON)
IF( LARGE_FILE_SUPPORT )
  SET(LARGE_FILE_MACROS "-D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64")
ENDIF()

## Test for Endianess
INCLUDE(TestBigEndian)
TEST_BIG_ENDIAN( BYTE_ORDER_BIG_ENDIAN )
IF( BYTE_ORDER_BIG_ENDIAN )
  ADD_DEFINITIONS("-DBIG_ENDIAN")
ELSE()
  ADD_DEFINITIONS("-DLITTLE_ENDIAN")
ENDIF()

##################################
## Common project configuration ##
##################################

#### Default build type
IF( NOT CMAKE_BUILD_TYPE )
  SET (CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING
      "Choose the type of build, RelWithDebInfo will be the default." FORCE)
ENDIF()

###########################
## Common compiler flags ##
###########################
IF( CMAKE_COMPILER_ID STREQUAL "GNU")
  SET(CXX_WARNING_LEVEL "-Wall -Werror -pedantic")
ELSEIF( CMAKE_CXX_COMPILER_ID STREQUAL "Clang" ) 
  SET(CXX_WARNING_LEVEL "-Wall -Werror -pedantic -Wdocumentation")
  ##SET(CXX_WARNING_LEVEL "${CXX_WARNING_LEVEL} -Wno-c++98-compat -Wno-c++98-compat-pedantic") ## No c++98 compatibility  
  ##SET(CXX_WARNING_LEVEL "${CXX_WARNING_LEVEL} -Wno-documentation-unknown-command") ## Disable error for unknown documentation commands
  ##SET(CXX_WARNING_LEVEL "${CXX_WARNING_LEVEL} -Wno-sign-conversion -Wno-conversion") ## Disable sign conversion error
  ##SET(CXX_WARNING_LEVEL "${CXX_WARNING_LEVEL} -Wno-exit-time-destructors -Wno-weak-vtables") ## Disable exit time destructor error
ENDIF()

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_WARNING_LEVEL} -std=c++11")
SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELEASE} -g")

ADD_DEFINITIONS("${LARGE_FILE_MACROS}")

#####################################
## Vendor dependent compiler flags ##
#####################################

IF( CMAKE_CXX_COMPILER_ID STREQUAL "GNU" )
  SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -pedantic")
ELSEIF( CMAKE_CXX_COMPILER_ID STREQUAL "Clang" ) 
  SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -pedantic")
ENDIF()

################
## Output log ##
################
STRING( TOUPPER "CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}" SPECIFIC_BUILD)
MESSAGE("############ COMPILER OPTIONS ############")
MESSAGE("Compiler ID : ${CMAKE_CXX_COMPILER_ID}")
MESSAGE("Compiler path : ${CMAKE_CXX_COMPILER}")
MESSAGE("Compiler version : ${CMAKE_CXX_COMPILER_VERSION}")
MESSAGE("CXX flags (base) : ${CMAKE_CXX_FLAGS}")
MESSAGE("CXX flags (build-type) : ${${SPECIFIC_BUILD}}")
MESSAGE("############ COMPILER OPTIONS ############")
##################
## Dependencies ##
##################

SET( CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake" )

FIND_PACKAGE( Boost 1.53 REQUIRED COMPONENTS filesystem system )

###################
## Import target ##
###################

ADD_SUBDIRECTORY( include  )
ADD_SUBDIRECTORY( src )
ADD_SUBDIRECTORY( qt )
ADD_SUBDIRECTORY( test )
ADD_SUBDIRECTORY( examples )
ADD_SUBDIRECTORY( doc )

#####################
## Exports targets ##
#####################

INSTALL(EXPORT Seismic DESTINATION lib)

#####################
## CPack variables ##
#####################

SET(CPACK_GENERATOR "TGZ;DEB")
SET(CPACK_PACKAGE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/packages)
SET(CPACK_PACKAGE_VERSION_MAJOR "${SeismicTraces_VERSION_MAJOR}")
SET(CPACK_PACKAGE_VERSION_MINOR "${SeismicTraces_VERSION_MINOR}")
SET(CPACK_SOURCE_IGNORE_FILES "/CVS/;/.svn/;.#;/#;.*~;cscope.*;/nbproject/;/build*/")

SET(CPACK_PACKAGE_CONTACT "Massimiliano Culpo")
INCLUDE( CPack )
