CMAKE_MINIMUM_REQUIRED(VERSION 2.8.7 FATAL_ERROR)
PROJECT(datas-and-algos-smhasher)

#set(CMAKE_VERBOSE_MAKEFILE on)

INCLUDE(ExternalProject)

SET_DIRECTORY_PROPERTIES(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/thirdparty)

ExternalProject_Add(
    smhasher
    SVN_REPOSITORY http://smhasher.googlecode.com/svn/trunk/
    TIMEOUT 10

    INSTALL_COMMAND ""
    BUILD_COMMAND ""
    CONFIGURE_COMMAND ""

    LOG_DOWNLOAD ON)

if(CMAKE_COMPILER_IS_GNUCXX)
  add_definitions("-std=c++0x")
endif(CMAKE_COMPILER_IS_GNUCXX)

ExternalProject_Get_Property(smhasher source_dir)
INCLUDE_DIRECTORIES(${source_dir})
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/../../src")
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/src")

ExternalProject_Get_Property(smhasher binary_dir)
LINK_DIRECTORIES(${binary_dir})

SET(smhasher-deps  
  ${source_dir}/KeysetTest.cpp
  ${source_dir}/Bitvec.cpp
  ${source_dir}/Stats.cpp
  ${source_dir}/MurmurHash3.cpp)

# this allows us to reference files in ADD_EXECUTABLE
# that do not exist yet
set_source_files_properties(
  ${smhasher-deps} PROPERTIES
  EXTERNAL_OBJECT TRUE
  GENERATED TRUE
)

ADD_EXECUTABLE(datas-and-algos-smhasher 
  ${PROJECT_SOURCE_DIR}/src/main.cpp 
  ${smhasher-deps})
ADD_DEPENDENCIES(datas-and-algos-smhasher smhasher)

