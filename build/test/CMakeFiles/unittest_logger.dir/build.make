# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/wkangk/tools

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wkangk/tools/build

# Include any dependencies generated for this target.
include test/CMakeFiles/unittest_logger.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/unittest_logger.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/unittest_logger.dir/flags.make

test/CMakeFiles/unittest_logger.dir/unittest_logger.cpp.o: test/CMakeFiles/unittest_logger.dir/flags.make
test/CMakeFiles/unittest_logger.dir/unittest_logger.cpp.o: ../test/unittest_logger.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wkangk/tools/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/unittest_logger.dir/unittest_logger.cpp.o"
	cd /home/wkangk/tools/build/test && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/unittest_logger.dir/unittest_logger.cpp.o -c /home/wkangk/tools/test/unittest_logger.cpp

test/CMakeFiles/unittest_logger.dir/unittest_logger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/unittest_logger.dir/unittest_logger.cpp.i"
	cd /home/wkangk/tools/build/test && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wkangk/tools/test/unittest_logger.cpp > CMakeFiles/unittest_logger.dir/unittest_logger.cpp.i

test/CMakeFiles/unittest_logger.dir/unittest_logger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/unittest_logger.dir/unittest_logger.cpp.s"
	cd /home/wkangk/tools/build/test && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wkangk/tools/test/unittest_logger.cpp -o CMakeFiles/unittest_logger.dir/unittest_logger.cpp.s

test/CMakeFiles/unittest_logger.dir/__/logger/logger.cpp.o: test/CMakeFiles/unittest_logger.dir/flags.make
test/CMakeFiles/unittest_logger.dir/__/logger/logger.cpp.o: ../logger/logger.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wkangk/tools/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object test/CMakeFiles/unittest_logger.dir/__/logger/logger.cpp.o"
	cd /home/wkangk/tools/build/test && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/unittest_logger.dir/__/logger/logger.cpp.o -c /home/wkangk/tools/logger/logger.cpp

test/CMakeFiles/unittest_logger.dir/__/logger/logger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/unittest_logger.dir/__/logger/logger.cpp.i"
	cd /home/wkangk/tools/build/test && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wkangk/tools/logger/logger.cpp > CMakeFiles/unittest_logger.dir/__/logger/logger.cpp.i

test/CMakeFiles/unittest_logger.dir/__/logger/logger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/unittest_logger.dir/__/logger/logger.cpp.s"
	cd /home/wkangk/tools/build/test && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wkangk/tools/logger/logger.cpp -o CMakeFiles/unittest_logger.dir/__/logger/logger.cpp.s

# Object files for target unittest_logger
unittest_logger_OBJECTS = \
"CMakeFiles/unittest_logger.dir/unittest_logger.cpp.o" \
"CMakeFiles/unittest_logger.dir/__/logger/logger.cpp.o"

# External object files for target unittest_logger
unittest_logger_EXTERNAL_OBJECTS =

test/unittest_logger: test/CMakeFiles/unittest_logger.dir/unittest_logger.cpp.o
test/unittest_logger: test/CMakeFiles/unittest_logger.dir/__/logger/logger.cpp.o
test/unittest_logger: test/CMakeFiles/unittest_logger.dir/build.make
test/unittest_logger: /usr/lib/x86_64-linux-gnu/libgflags.so.2.2.2
test/unittest_logger: /usr/local/lib/libgtest_main.a
test/unittest_logger: /usr/local/lib/libgtest.a
test/unittest_logger: test/CMakeFiles/unittest_logger.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wkangk/tools/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable unittest_logger"
	cd /home/wkangk/tools/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/unittest_logger.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/unittest_logger.dir/build: test/unittest_logger

.PHONY : test/CMakeFiles/unittest_logger.dir/build

test/CMakeFiles/unittest_logger.dir/clean:
	cd /home/wkangk/tools/build/test && $(CMAKE_COMMAND) -P CMakeFiles/unittest_logger.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/unittest_logger.dir/clean

test/CMakeFiles/unittest_logger.dir/depend:
	cd /home/wkangk/tools/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wkangk/tools /home/wkangk/tools/test /home/wkangk/tools/build /home/wkangk/tools/build/test /home/wkangk/tools/build/test/CMakeFiles/unittest_logger.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/unittest_logger.dir/depend
