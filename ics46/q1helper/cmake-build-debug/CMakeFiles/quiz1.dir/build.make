# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_COMMAND = /cygdrive/c/Users/Sq/.CLion2016.3/system/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/Users/Sq/.CLion2016.3/system/cygwin_cmake/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/cygdrive/d/ICS 46/q1helper"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/cygdrive/d/ICS 46/q1helper/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/quiz1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/quiz1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/quiz1.dir/flags.make

CMakeFiles/quiz1.dir/driver_quiz1.cpp.o: CMakeFiles/quiz1.dir/flags.make
CMakeFiles/quiz1.dir/driver_quiz1.cpp.o: ../driver_quiz1.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/cygdrive/d/ICS 46/q1helper/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/quiz1.dir/driver_quiz1.cpp.o"
	/cygdrive/c/cygwin64/bin/clang++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/quiz1.dir/driver_quiz1.cpp.o -c "/cygdrive/d/ICS 46/q1helper/driver_quiz1.cpp"

CMakeFiles/quiz1.dir/driver_quiz1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/quiz1.dir/driver_quiz1.cpp.i"
	/cygdrive/c/cygwin64/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/cygdrive/d/ICS 46/q1helper/driver_quiz1.cpp" > CMakeFiles/quiz1.dir/driver_quiz1.cpp.i

CMakeFiles/quiz1.dir/driver_quiz1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/quiz1.dir/driver_quiz1.cpp.s"
	/cygdrive/c/cygwin64/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/cygdrive/d/ICS 46/q1helper/driver_quiz1.cpp" -o CMakeFiles/quiz1.dir/driver_quiz1.cpp.s

CMakeFiles/quiz1.dir/driver_quiz1.cpp.o.requires:

.PHONY : CMakeFiles/quiz1.dir/driver_quiz1.cpp.o.requires

CMakeFiles/quiz1.dir/driver_quiz1.cpp.o.provides: CMakeFiles/quiz1.dir/driver_quiz1.cpp.o.requires
	$(MAKE) -f CMakeFiles/quiz1.dir/build.make CMakeFiles/quiz1.dir/driver_quiz1.cpp.o.provides.build
.PHONY : CMakeFiles/quiz1.dir/driver_quiz1.cpp.o.provides

CMakeFiles/quiz1.dir/driver_quiz1.cpp.o.provides.build: CMakeFiles/quiz1.dir/driver_quiz1.cpp.o


CMakeFiles/quiz1.dir/test_quiz1.cpp.o: CMakeFiles/quiz1.dir/flags.make
CMakeFiles/quiz1.dir/test_quiz1.cpp.o: ../test_quiz1.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/cygdrive/d/ICS 46/q1helper/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/quiz1.dir/test_quiz1.cpp.o"
	/cygdrive/c/cygwin64/bin/clang++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/quiz1.dir/test_quiz1.cpp.o -c "/cygdrive/d/ICS 46/q1helper/test_quiz1.cpp"

CMakeFiles/quiz1.dir/test_quiz1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/quiz1.dir/test_quiz1.cpp.i"
	/cygdrive/c/cygwin64/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/cygdrive/d/ICS 46/q1helper/test_quiz1.cpp" > CMakeFiles/quiz1.dir/test_quiz1.cpp.i

CMakeFiles/quiz1.dir/test_quiz1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/quiz1.dir/test_quiz1.cpp.s"
	/cygdrive/c/cygwin64/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/cygdrive/d/ICS 46/q1helper/test_quiz1.cpp" -o CMakeFiles/quiz1.dir/test_quiz1.cpp.s

CMakeFiles/quiz1.dir/test_quiz1.cpp.o.requires:

.PHONY : CMakeFiles/quiz1.dir/test_quiz1.cpp.o.requires

CMakeFiles/quiz1.dir/test_quiz1.cpp.o.provides: CMakeFiles/quiz1.dir/test_quiz1.cpp.o.requires
	$(MAKE) -f CMakeFiles/quiz1.dir/build.make CMakeFiles/quiz1.dir/test_quiz1.cpp.o.provides.build
.PHONY : CMakeFiles/quiz1.dir/test_quiz1.cpp.o.provides

CMakeFiles/quiz1.dir/test_quiz1.cpp.o.provides.build: CMakeFiles/quiz1.dir/test_quiz1.cpp.o


# Object files for target quiz1
quiz1_OBJECTS = \
"CMakeFiles/quiz1.dir/driver_quiz1.cpp.o" \
"CMakeFiles/quiz1.dir/test_quiz1.cpp.o"

# External object files for target quiz1
quiz1_EXTERNAL_OBJECTS =

quiz1.exe: CMakeFiles/quiz1.dir/driver_quiz1.cpp.o
quiz1.exe: CMakeFiles/quiz1.dir/test_quiz1.cpp.o
quiz1.exe: CMakeFiles/quiz1.dir/build.make
quiz1.exe: CMakeFiles/quiz1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/cygdrive/d/ICS 46/q1helper/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable quiz1.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/quiz1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/quiz1.dir/build: quiz1.exe

.PHONY : CMakeFiles/quiz1.dir/build

CMakeFiles/quiz1.dir/requires: CMakeFiles/quiz1.dir/driver_quiz1.cpp.o.requires
CMakeFiles/quiz1.dir/requires: CMakeFiles/quiz1.dir/test_quiz1.cpp.o.requires

.PHONY : CMakeFiles/quiz1.dir/requires

CMakeFiles/quiz1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/quiz1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/quiz1.dir/clean

CMakeFiles/quiz1.dir/depend:
	cd "/cygdrive/d/ICS 46/q1helper/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/cygdrive/d/ICS 46/q1helper" "/cygdrive/d/ICS 46/q1helper" "/cygdrive/d/ICS 46/q1helper/cmake-build-debug" "/cygdrive/d/ICS 46/q1helper/cmake-build-debug" "/cygdrive/d/ICS 46/q1helper/cmake-build-debug/CMakeFiles/quiz1.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/quiz1.dir/depend

