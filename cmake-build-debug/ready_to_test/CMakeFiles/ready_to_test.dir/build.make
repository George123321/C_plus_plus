# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.8

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\PF\JetBrains\CLion 2017.2.3\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "D:\PF\JetBrains\CLion 2017.2.3\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\George\Desktop\git_projects\C_plus_plus

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\George\Desktop\git_projects\C_plus_plus\cmake-build-debug

# Include any dependencies generated for this target.
include ready_to_test/CMakeFiles/ready_to_test.dir/depend.make

# Include the progress variables for this target.
include ready_to_test/CMakeFiles/ready_to_test.dir/progress.make

# Include the compile flags for this target's objects.
include ready_to_test/CMakeFiles/ready_to_test.dir/flags.make

ready_to_test/CMakeFiles/ready_to_test.dir/main.cpp.obj: ready_to_test/CMakeFiles/ready_to_test.dir/flags.make
ready_to_test/CMakeFiles/ready_to_test.dir/main.cpp.obj: ready_to_test/CMakeFiles/ready_to_test.dir/includes_CXX.rsp
ready_to_test/CMakeFiles/ready_to_test.dir/main.cpp.obj: ../ready_to_test/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\George\Desktop\git_projects\C_plus_plus\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object ready_to_test/CMakeFiles/ready_to_test.dir/main.cpp.obj"
	cd /d C:\Users\George\Desktop\git_projects\C_plus_plus\cmake-build-debug\ready_to_test && C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\ready_to_test.dir\main.cpp.obj -c C:\Users\George\Desktop\git_projects\C_plus_plus\ready_to_test\main.cpp

ready_to_test/CMakeFiles/ready_to_test.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ready_to_test.dir/main.cpp.i"
	cd /d C:\Users\George\Desktop\git_projects\C_plus_plus\cmake-build-debug\ready_to_test && C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\George\Desktop\git_projects\C_plus_plus\ready_to_test\main.cpp > CMakeFiles\ready_to_test.dir\main.cpp.i

ready_to_test/CMakeFiles/ready_to_test.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ready_to_test.dir/main.cpp.s"
	cd /d C:\Users\George\Desktop\git_projects\C_plus_plus\cmake-build-debug\ready_to_test && C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\George\Desktop\git_projects\C_plus_plus\ready_to_test\main.cpp -o CMakeFiles\ready_to_test.dir\main.cpp.s

ready_to_test/CMakeFiles/ready_to_test.dir/main.cpp.obj.requires:

.PHONY : ready_to_test/CMakeFiles/ready_to_test.dir/main.cpp.obj.requires

ready_to_test/CMakeFiles/ready_to_test.dir/main.cpp.obj.provides: ready_to_test/CMakeFiles/ready_to_test.dir/main.cpp.obj.requires
	$(MAKE) -f ready_to_test\CMakeFiles\ready_to_test.dir\build.make ready_to_test/CMakeFiles/ready_to_test.dir/main.cpp.obj.provides.build
.PHONY : ready_to_test/CMakeFiles/ready_to_test.dir/main.cpp.obj.provides

ready_to_test/CMakeFiles/ready_to_test.dir/main.cpp.obj.provides.build: ready_to_test/CMakeFiles/ready_to_test.dir/main.cpp.obj


# Object files for target ready_to_test
ready_to_test_OBJECTS = \
"CMakeFiles/ready_to_test.dir/main.cpp.obj"

# External object files for target ready_to_test
ready_to_test_EXTERNAL_OBJECTS =

ready_to_test/ready_to_test.exe: ready_to_test/CMakeFiles/ready_to_test.dir/main.cpp.obj
ready_to_test/ready_to_test.exe: ready_to_test/CMakeFiles/ready_to_test.dir/build.make
ready_to_test/ready_to_test.exe: ready_to_test/CMakeFiles/ready_to_test.dir/linklibs.rsp
ready_to_test/ready_to_test.exe: ready_to_test/CMakeFiles/ready_to_test.dir/objects1.rsp
ready_to_test/ready_to_test.exe: ready_to_test/CMakeFiles/ready_to_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\George\Desktop\git_projects\C_plus_plus\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ready_to_test.exe"
	cd /d C:\Users\George\Desktop\git_projects\C_plus_plus\cmake-build-debug\ready_to_test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\ready_to_test.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
ready_to_test/CMakeFiles/ready_to_test.dir/build: ready_to_test/ready_to_test.exe

.PHONY : ready_to_test/CMakeFiles/ready_to_test.dir/build

ready_to_test/CMakeFiles/ready_to_test.dir/requires: ready_to_test/CMakeFiles/ready_to_test.dir/main.cpp.obj.requires

.PHONY : ready_to_test/CMakeFiles/ready_to_test.dir/requires

ready_to_test/CMakeFiles/ready_to_test.dir/clean:
	cd /d C:\Users\George\Desktop\git_projects\C_plus_plus\cmake-build-debug\ready_to_test && $(CMAKE_COMMAND) -P CMakeFiles\ready_to_test.dir\cmake_clean.cmake
.PHONY : ready_to_test/CMakeFiles/ready_to_test.dir/clean

ready_to_test/CMakeFiles/ready_to_test.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\George\Desktop\git_projects\C_plus_plus C:\Users\George\Desktop\git_projects\C_plus_plus\ready_to_test C:\Users\George\Desktop\git_projects\C_plus_plus\cmake-build-debug C:\Users\George\Desktop\git_projects\C_plus_plus\cmake-build-debug\ready_to_test C:\Users\George\Desktop\git_projects\C_plus_plus\cmake-build-debug\ready_to_test\CMakeFiles\ready_to_test.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : ready_to_test/CMakeFiles/ready_to_test.dir/depend

