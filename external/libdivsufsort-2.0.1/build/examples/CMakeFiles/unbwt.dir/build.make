# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/daniel/Códigos/Semi-External-Landau-Vishkin/external/libdivsufsort-2.0.1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/daniel/Códigos/Semi-External-Landau-Vishkin/external/libdivsufsort-2.0.1/build

# Include any dependencies generated for this target.
include examples/CMakeFiles/unbwt.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/unbwt.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/unbwt.dir/flags.make

examples/CMakeFiles/unbwt.dir/unbwt.o: examples/CMakeFiles/unbwt.dir/flags.make
examples/CMakeFiles/unbwt.dir/unbwt.o: ../examples/unbwt.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/daniel/Códigos/Semi-External-Landau-Vishkin/external/libdivsufsort-2.0.1/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object examples/CMakeFiles/unbwt.dir/unbwt.o"
	cd /home/daniel/Códigos/Semi-External-Landau-Vishkin/external/libdivsufsort-2.0.1/build/examples && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/unbwt.dir/unbwt.o   -c /home/daniel/Códigos/Semi-External-Landau-Vishkin/external/libdivsufsort-2.0.1/examples/unbwt.c

examples/CMakeFiles/unbwt.dir/unbwt.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/unbwt.dir/unbwt.i"
	cd /home/daniel/Códigos/Semi-External-Landau-Vishkin/external/libdivsufsort-2.0.1/build/examples && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/daniel/Códigos/Semi-External-Landau-Vishkin/external/libdivsufsort-2.0.1/examples/unbwt.c > CMakeFiles/unbwt.dir/unbwt.i

examples/CMakeFiles/unbwt.dir/unbwt.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/unbwt.dir/unbwt.s"
	cd /home/daniel/Códigos/Semi-External-Landau-Vishkin/external/libdivsufsort-2.0.1/build/examples && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/daniel/Códigos/Semi-External-Landau-Vishkin/external/libdivsufsort-2.0.1/examples/unbwt.c -o CMakeFiles/unbwt.dir/unbwt.s

examples/CMakeFiles/unbwt.dir/unbwt.o.requires:
.PHONY : examples/CMakeFiles/unbwt.dir/unbwt.o.requires

examples/CMakeFiles/unbwt.dir/unbwt.o.provides: examples/CMakeFiles/unbwt.dir/unbwt.o.requires
	$(MAKE) -f examples/CMakeFiles/unbwt.dir/build.make examples/CMakeFiles/unbwt.dir/unbwt.o.provides.build
.PHONY : examples/CMakeFiles/unbwt.dir/unbwt.o.provides

examples/CMakeFiles/unbwt.dir/unbwt.o.provides.build: examples/CMakeFiles/unbwt.dir/unbwt.o

# Object files for target unbwt
unbwt_OBJECTS = \
"CMakeFiles/unbwt.dir/unbwt.o"

# External object files for target unbwt
unbwt_EXTERNAL_OBJECTS =

examples/unbwt: examples/CMakeFiles/unbwt.dir/unbwt.o
examples/unbwt: examples/CMakeFiles/unbwt.dir/build.make
examples/unbwt: lib/libdivsufsort.a
examples/unbwt: examples/CMakeFiles/unbwt.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable unbwt"
	cd /home/daniel/Códigos/Semi-External-Landau-Vishkin/external/libdivsufsort-2.0.1/build/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/unbwt.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/unbwt.dir/build: examples/unbwt
.PHONY : examples/CMakeFiles/unbwt.dir/build

examples/CMakeFiles/unbwt.dir/requires: examples/CMakeFiles/unbwt.dir/unbwt.o.requires
.PHONY : examples/CMakeFiles/unbwt.dir/requires

examples/CMakeFiles/unbwt.dir/clean:
	cd /home/daniel/Códigos/Semi-External-Landau-Vishkin/external/libdivsufsort-2.0.1/build/examples && $(CMAKE_COMMAND) -P CMakeFiles/unbwt.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/unbwt.dir/clean

examples/CMakeFiles/unbwt.dir/depend:
	cd /home/daniel/Códigos/Semi-External-Landau-Vishkin/external/libdivsufsort-2.0.1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/daniel/Códigos/Semi-External-Landau-Vishkin/external/libdivsufsort-2.0.1 /home/daniel/Códigos/Semi-External-Landau-Vishkin/external/libdivsufsort-2.0.1/examples /home/daniel/Códigos/Semi-External-Landau-Vishkin/external/libdivsufsort-2.0.1/build /home/daniel/Códigos/Semi-External-Landau-Vishkin/external/libdivsufsort-2.0.1/build/examples /home/daniel/Códigos/Semi-External-Landau-Vishkin/external/libdivsufsort-2.0.1/build/examples/CMakeFiles/unbwt.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/unbwt.dir/depend

