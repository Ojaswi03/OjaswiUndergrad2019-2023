# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.11

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_SOURCE_DIR = /s/bach/m/under/ojaswi/cs253/HW2/testdir

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /s/bach/m/under/ojaswi/cs253/HW2/testdir

# Include any dependencies generated for this target.
include CMakeFiles/hw2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/hw2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/hw2.dir/flags.make

CMakeFiles/hw2.dir/main.cc.o: CMakeFiles/hw2.dir/flags.make
CMakeFiles/hw2.dir/main.cc.o: main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/s/bach/m/under/ojaswi/cs253/HW2/testdir/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/hw2.dir/main.cc.o"
	/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hw2.dir/main.cc.o -c /s/bach/m/under/ojaswi/cs253/HW2/testdir/main.cc

CMakeFiles/hw2.dir/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hw2.dir/main.cc.i"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /s/bach/m/under/ojaswi/cs253/HW2/testdir/main.cc > CMakeFiles/hw2.dir/main.cc.i

CMakeFiles/hw2.dir/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hw2.dir/main.cc.s"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /s/bach/m/under/ojaswi/cs253/HW2/testdir/main.cc -o CMakeFiles/hw2.dir/main.cc.s

# Object files for target hw2
hw2_OBJECTS = \
"CMakeFiles/hw2.dir/main.cc.o"

# External object files for target hw2
hw2_EXTERNAL_OBJECTS =

hw2: CMakeFiles/hw2.dir/main.cc.o
hw2: CMakeFiles/hw2.dir/build.make
hw2: CMakeFiles/hw2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/s/bach/m/under/ojaswi/cs253/HW2/testdir/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable hw2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hw2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/hw2.dir/build: hw2

.PHONY : CMakeFiles/hw2.dir/build

CMakeFiles/hw2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/hw2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/hw2.dir/clean

CMakeFiles/hw2.dir/depend:
	cd /s/bach/m/under/ojaswi/cs253/HW2/testdir && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /s/bach/m/under/ojaswi/cs253/HW2/testdir /s/bach/m/under/ojaswi/cs253/HW2/testdir /s/bach/m/under/ojaswi/cs253/HW2/testdir /s/bach/m/under/ojaswi/cs253/HW2/testdir /s/bach/m/under/ojaswi/cs253/HW2/testdir/CMakeFiles/hw2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/hw2.dir/depend

