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
include CMakeFiles/threads.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/threads.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/threads.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/threads.dir/flags.make

CMakeFiles/threads.dir/threading-example.cpp.o: CMakeFiles/threads.dir/flags.make
CMakeFiles/threads.dir/threading-example.cpp.o: /Users/benschaser/Documents/Projects/raytracer/threading-example.cpp
CMakeFiles/threads.dir/threading-example.cpp.o: CMakeFiles/threads.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/benschaser/Documents/Projects/raytracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/threads.dir/threading-example.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/threads.dir/threading-example.cpp.o -MF CMakeFiles/threads.dir/threading-example.cpp.o.d -o CMakeFiles/threads.dir/threading-example.cpp.o -c /Users/benschaser/Documents/Projects/raytracer/threading-example.cpp

CMakeFiles/threads.dir/threading-example.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/threads.dir/threading-example.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/benschaser/Documents/Projects/raytracer/threading-example.cpp > CMakeFiles/threads.dir/threading-example.cpp.i

CMakeFiles/threads.dir/threading-example.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/threads.dir/threading-example.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/benschaser/Documents/Projects/raytracer/threading-example.cpp -o CMakeFiles/threads.dir/threading-example.cpp.s

# Object files for target threads
threads_OBJECTS = \
"CMakeFiles/threads.dir/threading-example.cpp.o"

# External object files for target threads
threads_EXTERNAL_OBJECTS =

threads: CMakeFiles/threads.dir/threading-example.cpp.o
threads: CMakeFiles/threads.dir/build.make
threads: CMakeFiles/threads.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/benschaser/Documents/Projects/raytracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable threads"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/threads.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/threads.dir/build: threads
.PHONY : CMakeFiles/threads.dir/build

CMakeFiles/threads.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/threads.dir/cmake_clean.cmake
.PHONY : CMakeFiles/threads.dir/clean

CMakeFiles/threads.dir/depend:
	cd /Users/benschaser/Documents/Projects/raytracer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/benschaser/Documents/Projects/raytracer /Users/benschaser/Documents/Projects/raytracer /Users/benschaser/Documents/Projects/raytracer/build /Users/benschaser/Documents/Projects/raytracer/build /Users/benschaser/Documents/Projects/raytracer/build/CMakeFiles/threads.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/threads.dir/depend

