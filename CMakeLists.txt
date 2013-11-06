cmake_minimum_required(VERSION 2.8)
#set(CMAKE_VERBOSE_MAKEFILE on)

option(SCAN_BUILD "Static analysis with clang's c++-analyzer" OFF)
if(SCAN_BUILD)
  # these SETs only work before any project() is declared
  SET(CCC_CXX "/usr/bin/clang++")
  SET(CMAKE_CXX_COMPILER "/usr/share/clang/scan-build/c++-analyzer")
  SET(CMAKE_CXX_FLAGS "-Weverything -g -std=c++11")
endif(SCAN_BUILD)

project(datas-and-algos)

add_definitions("-std=c++11")

if(CMAKE_COMPILER_IS_GNUCXX)
  add_definitions("-Wconversion" "-Wsign-conversion" "-Wextra" "-pedantic" "-Wall" "-Wextra" "-Wcast-align" "-Wcast-qual" "-Wctor-dtor-privacy" "-Wdisabled-optimization" "-Wformat=2" "-Winit-self" "-Wlogical-op" "-Wmissing-include-dirs" "-Woverloaded-virtual" "-Wredundant-decls" "-Wshadow" "-Wsign-promo" "-Wstrict-null-sentinel" "-Wstrict-overflow=5" "-Wswitch-default" "-Wundef" "-Wno-unused" "-Weffc++")
endif(CMAKE_COMPILER_IS_GNUCXX)

include_directories("${PROJECT_SOURCE_DIR}/src")

add_executable(data-structures src/main.cpp)

