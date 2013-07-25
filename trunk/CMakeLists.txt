CMAKE_MINIMUM_REQUIRED( VERSION 2.8.10 )
CMAKE_POLICY( VERSION 2.8.10 )

PROJECT( SeismicTraces C CXX )
SET( SeismicTraces_VERSION_MAJOR 1 )
SET( SeismicTraces_VERSION_MINOR 0 )

##################################
## Common project configuration ##
##################################

#### Default build type
IF (NOT CMAKE_BUILD_TYPE)
  SET (CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING
      "Choose the type of build, RelWithDebInfo will be the default." FORCE)
ENDIF()

#### Get compiler names
GET_FILENAME_COMPONENT( C_COMPILER_NAME ${CMAKE_C_COMPILER} NAME )

#### Detect Intel compiler
IF( C_COMPILER_NAME STREQUAL "icc" )
  SET( CMAKE_COMPILER_IS_INTEL TRUE )
ENDIF()

#### Set pedantic flag
IF( CMAKE_COMPILER_IS_GNUCC )
  SET(PEDANTIC_FLAG "-pedantic")
ENDIF()

#### Set default warning level for compilation
SET( C_WARNING_LEVEL "-Wall -Werror ${PEDANTIC_FLAG}")

#############################
## C project configuration ##
#############################

#### GNU / Intel
IF( CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_INTEL )
  SET(CMAKE_C_FLAGS_DEBUG "-O0 -g ${C_WARNING_LEVEL} -std=c99")
  SET(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG ${C_WARNING_LEVEL} -std=c99")
  SET(CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELEASE} -g")
ENDIF()

###############################
## CXX project configuration ##
###############################

#### GNU / Intel
IF( CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_INTEL )
  SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -g ${C_WARNING_LEVEL} -std=c++0x")
  SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG ${C_WARNING_LEVEL} -std=c++0x")
  SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELEASE} -g")
ENDIF()

#### GET COMPILER VERSION
EXEC_PROGRAM(	  
  ${CMAKE_CXX_COMPILER}
  ARGS ${CMAKE_CXX_COMPILER_ARG1} -dumpversion
  OUTPUT_VARIABLE COMPILER_VERSION
)

string(
  REGEX REPLACE "([0-9])\\.([0-9])(\\.[0-9])?" "\\1"
  COMPILER_VERSION_MAJOR ${COMPILER_VERSION}
)

string(
  REGEX REPLACE "([0-9])\\.([0-9])(\\.[0-9])?" "\\2"
  COMPILER_VERSION_MINOR ${COMPILER_VERSION}
)

###################
## Build options ##
###################

OPTION(BUILD_SHARED_LIBS "Create shared libraries instead of static ones (default OFF)" OFF)
OPTION(BUILD_UTILITIES "Enable the build of the utilities bundled with the library. Require Boost" ON)

##################
## Dependencies ##
##################

###################
## Import target ##
###################

ADD_SUBDIRECTORY( examples )
