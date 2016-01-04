cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project("Malloc Count" C)

SET(optmization_flags " -std=c++11 -O2 ")
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_CXX_FLAGS "-O2 -std=c++11") 

add_library(malloc_count STATIC malloc_count.c stack_count.c malloc_count.h stack_count.h memprofile.h)
install(TARGETS malloc_count ARCHIVE DESTINATION lib)
