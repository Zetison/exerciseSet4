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
CMAKE_SOURCE_DIR = /home/shomec/j/jonvegar/TMA4280/exerciseSet4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/shomec/j/jonvegar/TMA4280/exerciseSet4/build

# Include any dependencies generated for this target.
include CMakeFiles/compute_S_OpenMP.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/compute_S_OpenMP.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/compute_S_OpenMP.dir/flags.make

CMakeFiles/compute_S_OpenMP.dir/compute_S_OpenMP.c.o: CMakeFiles/compute_S_OpenMP.dir/flags.make
CMakeFiles/compute_S_OpenMP.dir/compute_S_OpenMP.c.o: ../compute_S_OpenMP.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/shomec/j/jonvegar/TMA4280/exerciseSet4/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/compute_S_OpenMP.dir/compute_S_OpenMP.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/compute_S_OpenMP.dir/compute_S_OpenMP.c.o   -c /home/shomec/j/jonvegar/TMA4280/exerciseSet4/compute_S_OpenMP.c

CMakeFiles/compute_S_OpenMP.dir/compute_S_OpenMP.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/compute_S_OpenMP.dir/compute_S_OpenMP.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/shomec/j/jonvegar/TMA4280/exerciseSet4/compute_S_OpenMP.c > CMakeFiles/compute_S_OpenMP.dir/compute_S_OpenMP.c.i

CMakeFiles/compute_S_OpenMP.dir/compute_S_OpenMP.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/compute_S_OpenMP.dir/compute_S_OpenMP.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/shomec/j/jonvegar/TMA4280/exerciseSet4/compute_S_OpenMP.c -o CMakeFiles/compute_S_OpenMP.dir/compute_S_OpenMP.c.s

CMakeFiles/compute_S_OpenMP.dir/compute_S_OpenMP.c.o.requires:
.PHONY : CMakeFiles/compute_S_OpenMP.dir/compute_S_OpenMP.c.o.requires

CMakeFiles/compute_S_OpenMP.dir/compute_S_OpenMP.c.o.provides: CMakeFiles/compute_S_OpenMP.dir/compute_S_OpenMP.c.o.requires
	$(MAKE) -f CMakeFiles/compute_S_OpenMP.dir/build.make CMakeFiles/compute_S_OpenMP.dir/compute_S_OpenMP.c.o.provides.build
.PHONY : CMakeFiles/compute_S_OpenMP.dir/compute_S_OpenMP.c.o.provides

CMakeFiles/compute_S_OpenMP.dir/compute_S_OpenMP.c.o.provides.build: CMakeFiles/compute_S_OpenMP.dir/compute_S_OpenMP.c.o

# Object files for target compute_S_OpenMP
compute_S_OpenMP_OBJECTS = \
"CMakeFiles/compute_S_OpenMP.dir/compute_S_OpenMP.c.o"

# External object files for target compute_S_OpenMP
compute_S_OpenMP_EXTERNAL_OBJECTS =

compute_S_OpenMP: CMakeFiles/compute_S_OpenMP.dir/compute_S_OpenMP.c.o
compute_S_OpenMP: CMakeFiles/compute_S_OpenMP.dir/build.make
compute_S_OpenMP: libutils.a
compute_S_OpenMP: CMakeFiles/compute_S_OpenMP.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable compute_S_OpenMP"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/compute_S_OpenMP.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/compute_S_OpenMP.dir/build: compute_S_OpenMP
.PHONY : CMakeFiles/compute_S_OpenMP.dir/build

CMakeFiles/compute_S_OpenMP.dir/requires: CMakeFiles/compute_S_OpenMP.dir/compute_S_OpenMP.c.o.requires
.PHONY : CMakeFiles/compute_S_OpenMP.dir/requires

CMakeFiles/compute_S_OpenMP.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/compute_S_OpenMP.dir/cmake_clean.cmake
.PHONY : CMakeFiles/compute_S_OpenMP.dir/clean

CMakeFiles/compute_S_OpenMP.dir/depend:
	cd /home/shomec/j/jonvegar/TMA4280/exerciseSet4/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/shomec/j/jonvegar/TMA4280/exerciseSet4 /home/shomec/j/jonvegar/TMA4280/exerciseSet4 /home/shomec/j/jonvegar/TMA4280/exerciseSet4/build /home/shomec/j/jonvegar/TMA4280/exerciseSet4/build /home/shomec/j/jonvegar/TMA4280/exerciseSet4/build/CMakeFiles/compute_S_OpenMP.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/compute_S_OpenMP.dir/depend
