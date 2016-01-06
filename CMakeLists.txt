cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project("Landau Vishkin Library" CXX)
include(ExternalProject)
SET(optmization_flags " -std=c++11 -O2 ")
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_CXX_FLAGS "-O2 -std=c++11") 


### EXTERNAL LIBRARIES ###
ExternalProject_Add(project_malloc_count
    GIT_REPOSITORY https://github.com/danielsaad/malloc_count
    PREFIX "project_malloc_count"
)

ExternalProject_Get_Property(project_malloc_count install_dir)
add_library(libmalloc_count STATIC IMPORTED)
set_property(TARGET libmalloc_count PROPERTY IMPORTED_LOCATION ${install_dir}/lib/libmalloc_count.a)
add_dependencies(libmalloc_count project_malloc_count)



ExternalProject_Add(project_libdivsufsort
    GIT_REPOSITORY https://github.com/danielsaad/libdivsufsort
    PREFIX "project_libdivsudsort"
    CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=."
)

ExternalProject_Get_Property(project_libdivsufsort install_dir)
add_library(libdivsufsort STATIC IMPORTED)
add_library(libdivsufsort64 STATIC IMPORTED)
MESSAGE(STATUS "Installdir eh = " ${install_dir})
set_property(TARGET libdivsufsort PROPERTY IMPORTED_LOCATION ${install_dir}/lib/libdivsufsort.a)
set_property(TARGET libdivsufsort PROPERTY IMPORTED_LOCATION ${install_dir}/lib/libdivsufsort64.a)
add_dependencies(libdivsufsort project_libdivsufsort)

include_directories(${install_dir}/include)

#set(LIBDIVSUFSORT_DIR "${CMAKE_SOURCE_DIR}/external/libdivsufsort-2.0.1")
#include_directories("${LIBDIVSUFSORT_DIR}/include")
include_directories("${CMAKE_SOURCE_DIR}/include")


add_subdirectory("${CMAKE_SOURCE_DIR}/src")
add_subdirectory("${CMAKE_SOURCE_DIR}/example")
add_subdirectory("${CMAKE_SOURCE_DIR}/benchmark")



