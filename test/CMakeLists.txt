# Tests
# also downloads & builds googletest

# https://gist.github.com/oneamtu/3734295
# http://stackoverflow.com/questions/9689183/cmake-googletest

CMAKE_MINIMUM_REQUIRED(VERSION 2.8.7 FATAL_ERROR)
PROJECT(data-structures-test)

#set(CMAKE_VERBOSE_MAKEFILE on)

INCLUDE(ExternalProject)

SET_DIRECTORY_PROPERTIES(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/thirdparty)

ExternalProject_Add(
    googletest
    URL http://googletest.googlecode.com/files/gtest-1.6.0.zip
    TIMEOUT 10

    # googletest has no install target
    INSTALL_COMMAND ""

    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON)

if(CMAKE_COMPILER_IS_GNUCXX)
  add_definitions("-std=c++0x")
endif(CMAKE_COMPILER_IS_GNUCXX)

ExternalProject_Get_Property(googletest source_dir)
INCLUDE_DIRECTORIES(${source_dir}/include)
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/../src")
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/src")

ExternalProject_Get_Property(googletest binary_dir)
LINK_DIRECTORIES(${binary_dir})

ADD_EXECUTABLE(data-structures-test ${PROJECT_SOURCE_DIR}/src/main.cpp)
ADD_DEPENDENCIES(data-structures-test googletest)

TARGET_LINK_LIBRARIES(data-structures-test gtest)
TARGET_LINK_LIBRARIES(data-structures-test pthread)

