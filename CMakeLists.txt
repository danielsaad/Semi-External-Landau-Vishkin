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
add_library(lib_malloc_count STATIC IMPORTED)
set_property(TARGET lib_malloc_count PROPERTY IMPORTED_LOCATION ${install_dir}/src/project_malloc_count/lib/libmalloc_count.a)
add_dependencies(lib_malloc_count project_malloc_count)



ExternalProject_Add(project_libdivsufsort
    GIT_REPOSITORY https://github.com/danielsaad/libdivsufsort
    PREFIX "project_libdivsudsort"
    CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=."
)

ExternalProject_Get_Property(project_libdivsufsort install_dir)
add_library(lib_divsufsort STATIC IMPORTED)
add_library(lib_divsufsort64 STATIC IMPORTED)
set_property(TARGET lib_divsufsort PROPERTY IMPORTED_LOCATION ${install_dir}/src/project_libdivsufsort-build/lib/libdivsufsort.a)
set_property(TARGET lib_divsufsort64 PROPERTY IMPORTED_LOCATION ${install_dir}/src/project_libdivsufsort-build/lib/libdivsufsort64.a)
add_dependencies(lib_divsufsort project_libdivsufsort)
add_dependencies(lib_divsufsort64 project_libdivsufsort)

include_directories(${install_dir}/src/project_libdivsufsort-build/include)

include_directories("${CMAKE_SOURCE_DIR}/include")
add_subdirectory("${CMAKE_SOURCE_DIR}/src")
add_subdirectory("${CMAKE_SOURCE_DIR}/example")
add_subdirectory("${CMAKE_SOURCE_DIR}/benchmark")



