# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/me/Projects/CPP/dropMath/test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/me/Projects/CPP/dropMath/test/build

# Include any dependencies generated for this target.
include CMakeFiles/drop_math_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/drop_math_test.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/drop_math_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/drop_math_test.dir/flags.make

CMakeFiles/drop_math_test.dir/test.cpp.o: CMakeFiles/drop_math_test.dir/flags.make
CMakeFiles/drop_math_test.dir/test.cpp.o: ../test.cpp
CMakeFiles/drop_math_test.dir/test.cpp.o: CMakeFiles/drop_math_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/me/Projects/CPP/dropMath/test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/drop_math_test.dir/test.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/drop_math_test.dir/test.cpp.o -MF CMakeFiles/drop_math_test.dir/test.cpp.o.d -o CMakeFiles/drop_math_test.dir/test.cpp.o -c /home/me/Projects/CPP/dropMath/test/test.cpp

CMakeFiles/drop_math_test.dir/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/drop_math_test.dir/test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/me/Projects/CPP/dropMath/test/test.cpp > CMakeFiles/drop_math_test.dir/test.cpp.i

CMakeFiles/drop_math_test.dir/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/drop_math_test.dir/test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/me/Projects/CPP/dropMath/test/test.cpp -o CMakeFiles/drop_math_test.dir/test.cpp.s

# Object files for target drop_math_test
drop_math_test_OBJECTS = \
"CMakeFiles/drop_math_test.dir/test.cpp.o"

# External object files for target drop_math_test
drop_math_test_EXTERNAL_OBJECTS =

drop_math_test: CMakeFiles/drop_math_test.dir/test.cpp.o
drop_math_test: CMakeFiles/drop_math_test.dir/build.make
drop_math_test: CMakeFiles/drop_math_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/me/Projects/CPP/dropMath/test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable drop_math_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/drop_math_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/drop_math_test.dir/build: drop_math_test
.PHONY : CMakeFiles/drop_math_test.dir/build

CMakeFiles/drop_math_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/drop_math_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/drop_math_test.dir/clean

CMakeFiles/drop_math_test.dir/depend:
	cd /home/me/Projects/CPP/dropMath/test/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/me/Projects/CPP/dropMath/test /home/me/Projects/CPP/dropMath/test /home/me/Projects/CPP/dropMath/test/build /home/me/Projects/CPP/dropMath/test/build /home/me/Projects/CPP/dropMath/test/build/CMakeFiles/drop_math_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/drop_math_test.dir/depend

