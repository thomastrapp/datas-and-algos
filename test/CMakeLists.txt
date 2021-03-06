# Tests
# also downloads & builds googletest

# https://gist.github.com/oneamtu/3734295
# http://stackoverflow.com/questions/9689183/cmake-googletest

CMAKE_MINIMUM_REQUIRED(VERSION 2.8.7 FATAL_ERROR)
PROJECT(datas-and-algos-test)

#set(CMAKE_VERBOSE_MAKEFILE on)

INCLUDE(ExternalProject)

SET_DIRECTORY_PROPERTIES(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/thirdparty)

ExternalProject_Add(
    googletest
    URL http://googletest.googlecode.com/files/gtest-1.7.0.zip
    TIMEOUT 10

    # googletest has no install target
    INSTALL_COMMAND ""

    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON)

add_definitions("-std=c++11")

ExternalProject_Get_Property(googletest source_dir)
INCLUDE_DIRECTORIES(${source_dir}/include)
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/../src")
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/src")

ExternalProject_Get_Property(googletest binary_dir)
LINK_DIRECTORIES(${binary_dir})

ADD_EXECUTABLE(datas-and-algos-test ${PROJECT_SOURCE_DIR}/src/main.cpp)
ADD_DEPENDENCIES(datas-and-algos-test googletest)

TARGET_LINK_LIBRARIES(datas-and-algos-test gtest)
TARGET_LINK_LIBRARIES(datas-and-algos-test pthread)

