# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.25.0/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.25.0/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/benschaser/Documents/Projects/raytracer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/benschaser/Documents/Projects/raytracer/build

# Include any dependencies generated for this target.
include CMakeFiles/material.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/material.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/material.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/material.dir/flags.make

CMakeFiles/material.dir/material.cpp.o: CMakeFiles/material.dir/flags.make
CMakeFiles/material.dir/material.cpp.o: /Users/benschaser/Documents/Projects/raytracer/material.cpp
CMakeFiles/material.dir/material.cpp.o: CMakeFiles/material.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/benschaser/Documents/Projects/raytracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/material.dir/material.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/material.dir/material.cpp.o -MF CMakeFiles/material.dir/material.cpp.o.d -o CMakeFiles/material.dir/material.cpp.o -c /Users/benschaser/Documents/Projects/raytracer/material.cpp

CMakeFiles/material.dir/material.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/material.dir/material.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/benschaser/Documents/Projects/raytracer/material.cpp > CMakeFiles/material.dir/material.cpp.i

CMakeFiles/material.dir/material.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/material.dir/material.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/benschaser/Documents/Projects/raytracer/material.cpp -o CMakeFiles/material.dir/material.cpp.s

# Object files for target material
material_OBJECTS = \
"CMakeFiles/material.dir/material.cpp.o"

# External object files for target material
material_EXTERNAL_OBJECTS =

libmaterial.a: CMakeFiles/material.dir/material.cpp.o
libmaterial.a: CMakeFiles/material.dir/build.make
libmaterial.a: CMakeFiles/material.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/benschaser/Documents/Projects/raytracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libmaterial.a"
	$(CMAKE_COMMAND) -P CMakeFiles/material.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/material.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/material.dir/build: libmaterial.a
.PHONY : CMakeFiles/material.dir/build

CMakeFiles/material.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/material.dir/cmake_clean.cmake
.PHONY : CMakeFiles/material.dir/clean

CMakeFiles/material.dir/depend:
	cd /Users/benschaser/Documents/Projects/raytracer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/benschaser/Documents/Projects/raytracer /Users/benschaser/Documents/Projects/raytracer /Users/benschaser/Documents/Projects/raytracer/build /Users/benschaser/Documents/Projects/raytracer/build /Users/benschaser/Documents/Projects/raytracer/build/CMakeFiles/material.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/material.dir/depend

