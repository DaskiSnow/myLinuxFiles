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
CMAKE_SOURCE_DIR = /home/daskisnow/myLinuxFiles/rd01

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/daskisnow/myLinuxFiles/rd01/build

# Include any dependencies generated for this target.
include src/CMakeFiles/main.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/main.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/main.dir/flags.make

src/CMakeFiles/main.dir/func.cc.o: src/CMakeFiles/main.dir/flags.make
src/CMakeFiles/main.dir/func.cc.o: ../src/func.cc
src/CMakeFiles/main.dir/func.cc.o: src/CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/daskisnow/myLinuxFiles/rd01/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/main.dir/func.cc.o"
	cd /home/daskisnow/myLinuxFiles/rd01/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/main.dir/func.cc.o -MF CMakeFiles/main.dir/func.cc.o.d -o CMakeFiles/main.dir/func.cc.o -c /home/daskisnow/myLinuxFiles/rd01/src/func.cc

src/CMakeFiles/main.dir/func.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/func.cc.i"
	cd /home/daskisnow/myLinuxFiles/rd01/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/daskisnow/myLinuxFiles/rd01/src/func.cc > CMakeFiles/main.dir/func.cc.i

src/CMakeFiles/main.dir/func.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/func.cc.s"
	cd /home/daskisnow/myLinuxFiles/rd01/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/daskisnow/myLinuxFiles/rd01/src/func.cc -o CMakeFiles/main.dir/func.cc.s

src/CMakeFiles/main.dir/main.cc.o: src/CMakeFiles/main.dir/flags.make
src/CMakeFiles/main.dir/main.cc.o: ../src/main.cc
src/CMakeFiles/main.dir/main.cc.o: src/CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/daskisnow/myLinuxFiles/rd01/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/main.dir/main.cc.o"
	cd /home/daskisnow/myLinuxFiles/rd01/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/main.dir/main.cc.o -MF CMakeFiles/main.dir/main.cc.o.d -o CMakeFiles/main.dir/main.cc.o -c /home/daskisnow/myLinuxFiles/rd01/src/main.cc

src/CMakeFiles/main.dir/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/main.cc.i"
	cd /home/daskisnow/myLinuxFiles/rd01/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/daskisnow/myLinuxFiles/rd01/src/main.cc > CMakeFiles/main.dir/main.cc.i

src/CMakeFiles/main.dir/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/main.cc.s"
	cd /home/daskisnow/myLinuxFiles/rd01/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/daskisnow/myLinuxFiles/rd01/src/main.cc -o CMakeFiles/main.dir/main.cc.s

src/CMakeFiles/main.dir/testFunc1.cc.o: src/CMakeFiles/main.dir/flags.make
src/CMakeFiles/main.dir/testFunc1.cc.o: ../src/testFunc1.cc
src/CMakeFiles/main.dir/testFunc1.cc.o: src/CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/daskisnow/myLinuxFiles/rd01/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/main.dir/testFunc1.cc.o"
	cd /home/daskisnow/myLinuxFiles/rd01/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/main.dir/testFunc1.cc.o -MF CMakeFiles/main.dir/testFunc1.cc.o.d -o CMakeFiles/main.dir/testFunc1.cc.o -c /home/daskisnow/myLinuxFiles/rd01/src/testFunc1.cc

src/CMakeFiles/main.dir/testFunc1.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/testFunc1.cc.i"
	cd /home/daskisnow/myLinuxFiles/rd01/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/daskisnow/myLinuxFiles/rd01/src/testFunc1.cc > CMakeFiles/main.dir/testFunc1.cc.i

src/CMakeFiles/main.dir/testFunc1.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/testFunc1.cc.s"
	cd /home/daskisnow/myLinuxFiles/rd01/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/daskisnow/myLinuxFiles/rd01/src/testFunc1.cc -o CMakeFiles/main.dir/testFunc1.cc.s

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/func.cc.o" \
"CMakeFiles/main.dir/main.cc.o" \
"CMakeFiles/main.dir/testFunc1.cc.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

../bin/main: src/CMakeFiles/main.dir/func.cc.o
../bin/main: src/CMakeFiles/main.dir/main.cc.o
../bin/main: src/CMakeFiles/main.dir/testFunc1.cc.o
../bin/main: src/CMakeFiles/main.dir/build.make
../bin/main: src/CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/daskisnow/myLinuxFiles/rd01/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable ../../bin/main"
	cd /home/daskisnow/myLinuxFiles/rd01/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/main.dir/build: ../bin/main
.PHONY : src/CMakeFiles/main.dir/build

src/CMakeFiles/main.dir/clean:
	cd /home/daskisnow/myLinuxFiles/rd01/build/src && $(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/main.dir/clean

src/CMakeFiles/main.dir/depend:
	cd /home/daskisnow/myLinuxFiles/rd01/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/daskisnow/myLinuxFiles/rd01 /home/daskisnow/myLinuxFiles/rd01/src /home/daskisnow/myLinuxFiles/rd01/build /home/daskisnow/myLinuxFiles/rd01/build/src /home/daskisnow/myLinuxFiles/rd01/build/src/CMakeFiles/main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/main.dir/depend
