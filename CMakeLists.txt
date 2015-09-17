cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project("Landau Vishkin Library" CXX)

SET(optmization_flags " -std=c++11 -O2 ")
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_CXX_FLAGS "-O2 -std=c++11") 



set(LIBDIVSUFSORT_DIR "${CMAKE_SOURCE_DIR}/external/libdivsufsort-2.0.1")
include_directories("${LIBDIVSUFSORT_DIR}/include")
include_directories("${CMAKE_SOURCE_DIR}/include")

#adding libraries
link_directories("${CMAKE_SOURCE_DIR}/lib")

add_subdirectory("${CMAKE_SOURCE_DIR}/src")
add_subdirectory("${CMAKE_SOURCE_DIR}/example")




