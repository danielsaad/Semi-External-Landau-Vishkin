cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project("Landau Vishkin Library" CXX)

#SET(warnings " -Wall -Werror -Wextra ")
SET(optmization_flags " -std=c++11 -O2 ")
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_CXX_FLAGS "-O2 -std=c++11") 
#if (NOT CONFIGURED_ONCE)
   
 #       CACHE STRING "Flags used by the compiler during all build types." FORCE)
#endif()




set(LIBDIVSUFSORT_DIR "${CMAKE_BINARY_DIR}/external/libdivsufsort-2.0.1")
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
add_subdirectory("external/libdivsufsort-2.0.1")
include_directories("${LIBDIVSUFSORT_DIR}/include")
include_directories("./include")
add_subdirectory(${SOURCE_DIR})
add_subdirectory("./example")


#set(CONFIGURED_ONCE TRUE CACHE INTERNAL 
#	"A flag showing that CMake has configured at least once.")
