cmake_minimum_required(VERSION 2.8)
#set(CMAKE_VERBOSE_MAKEFILE on)

option(SCAN_BUILD "Static analysis with clang's c++-analyzer" OFF)
if(SCAN_BUILD)
  # forcing the compiler is only possible before any project() is declared
  SET(CCC_CXX "/usr/bin/clang++")
  SET(CMAKE_CXX_COMPILER "/usr/share/clang/scan-build/c++-analyzer")
  SET(CMAKE_CXX_FLAGS "-Weverything -g -std=c++11")
endif(SCAN_BUILD)

project(datas-and-algos)

add_definitions("-std=c++11")

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  add_definitions("-Weverything")
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
  # removed "-Wsign-conversion"; see this bug 
  # https://gcc.gnu.org/bugzilla/show_bug.cgi?id=60342
  # and this
  # https://gcc.gnu.org/bugzilla/show_bug.cgi?id=49626
  add_definitions("-Wconversion" "-Wextra" "-pedantic" "-Wall" "-Wextra" "-Wcast-align" "-Wcast-qual" "-Wctor-dtor-privacy" "-Wdisabled-optimization" "-Wformat=2" "-Winit-self" "-Wlogical-op" "-Wmissing-include-dirs" "-Woverloaded-virtual" "-Wredundant-decls" "-Wshadow" "-Wsign-promo" "-Wstrict-null-sentinel" "-Wstrict-overflow=5" "-Wswitch-default" "-Wundef" "-Wno-unused" "-Weffc++")
endif(CMAKE_COMPILER_IS_GNUCXX)

include_directories("${PROJECT_SOURCE_DIR}/src")

add_executable(datas-and-algos src/main.cpp)

option(TCMALLOC "Link with libtcmalloc" OFF)
if(TCMALLOC)
  target_link_libraries(datas-and-algos tcmalloc)

  # remove this if you didn't configure gperftools with
  # --enable-frame-pointers (recommended for x86_64)
  add_definitions("-fno-omit-frame-pointer")
endif(TCMALLOC)

option(SYMBOLS "Add debugging symbols" OFF)
if(SYMBOLS)
  add_definitions("-g")
endif(SYMBOLS)

