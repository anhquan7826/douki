# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/anhquan7826/Desktop/unisync/unisync_linux

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/anhquan7826/Desktop/unisync/unisync_linux/build

# Include any dependencies generated for this target.
include CMakeFiles/unisync_linux.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/unisync_linux.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/unisync_linux.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/unisync_linux.dir/flags.make

CMakeFiles/unisync_linux.dir/src/main.c.o: CMakeFiles/unisync_linux.dir/flags.make
CMakeFiles/unisync_linux.dir/src/main.c.o: /home/anhquan7826/Desktop/unisync/unisync_linux/src/main.c
CMakeFiles/unisync_linux.dir/src/main.c.o: CMakeFiles/unisync_linux.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/anhquan7826/Desktop/unisync/unisync_linux/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/unisync_linux.dir/src/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/unisync_linux.dir/src/main.c.o -MF CMakeFiles/unisync_linux.dir/src/main.c.o.d -o CMakeFiles/unisync_linux.dir/src/main.c.o -c /home/anhquan7826/Desktop/unisync/unisync_linux/src/main.c

CMakeFiles/unisync_linux.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/unisync_linux.dir/src/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/anhquan7826/Desktop/unisync/unisync_linux/src/main.c > CMakeFiles/unisync_linux.dir/src/main.c.i

CMakeFiles/unisync_linux.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/unisync_linux.dir/src/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/anhquan7826/Desktop/unisync/unisync_linux/src/main.c -o CMakeFiles/unisync_linux.dir/src/main.c.s

# Object files for target unisync_linux
unisync_linux_OBJECTS = \
"CMakeFiles/unisync_linux.dir/src/main.c.o"

# External object files for target unisync_linux
unisync_linux_EXTERNAL_OBJECTS =

unisync_linux: CMakeFiles/unisync_linux.dir/src/main.c.o
unisync_linux: CMakeFiles/unisync_linux.dir/build.make
unisync_linux: CMakeFiles/unisync_linux.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/anhquan7826/Desktop/unisync/unisync_linux/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable unisync_linux"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/unisync_linux.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/unisync_linux.dir/build: unisync_linux
.PHONY : CMakeFiles/unisync_linux.dir/build

CMakeFiles/unisync_linux.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/unisync_linux.dir/cmake_clean.cmake
.PHONY : CMakeFiles/unisync_linux.dir/clean

CMakeFiles/unisync_linux.dir/depend:
	cd /home/anhquan7826/Desktop/unisync/unisync_linux/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/anhquan7826/Desktop/unisync/unisync_linux /home/anhquan7826/Desktop/unisync/unisync_linux /home/anhquan7826/Desktop/unisync/unisync_linux/build /home/anhquan7826/Desktop/unisync/unisync_linux/build /home/anhquan7826/Desktop/unisync/unisync_linux/build/CMakeFiles/unisync_linux.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/unisync_linux.dir/depend
