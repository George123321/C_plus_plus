# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.9

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
CMAKE_SOURCE_DIR = C:\Users\George\Desktop\git_projects\C_plus_plus\DV_HW

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\George\Desktop\git_projects\C_plus_plus\DV_HW\cmake-build-debug

# Include any dependencies generated for this target.
include 1_a_iii/CMakeFiles/DV_HW_3.dir/depend.make

# Include the progress variables for this target.
include 1_a_iii/CMakeFiles/DV_HW_3.dir/progress.make

# Include the compile flags for this target's objects.
include 1_a_iii/CMakeFiles/DV_HW_3.dir/flags.make

1_a_iii/CMakeFiles/DV_HW_3.dir/1_a_iii.c.obj: 1_a_iii/CMakeFiles/DV_HW_3.dir/flags.make
1_a_iii/CMakeFiles/DV_HW_3.dir/1_a_iii.c.obj: ../1_a_iii/1_a_iii.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\George\Desktop\git_projects\C_plus_plus\DV_HW\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object 1_a_iii/CMakeFiles/DV_HW_3.dir/1_a_iii.c.obj"
	cd /d C:\Users\George\Desktop\git_projects\C_plus_plus\DV_HW\cmake-build-debug\1_a_iii && C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\DV_HW_3.dir\1_a_iii.c.obj   -c C:\Users\George\Desktop\git_projects\C_plus_plus\DV_HW\1_a_iii\1_a_iii.c

1_a_iii/CMakeFiles/DV_HW_3.dir/1_a_iii.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/DV_HW_3.dir/1_a_iii.c.i"
	cd /d C:\Users\George\Desktop\git_projects\C_plus_plus\DV_HW\cmake-build-debug\1_a_iii && C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\George\Desktop\git_projects\C_plus_plus\DV_HW\1_a_iii\1_a_iii.c > CMakeFiles\DV_HW_3.dir\1_a_iii.c.i

1_a_iii/CMakeFiles/DV_HW_3.dir/1_a_iii.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/DV_HW_3.dir/1_a_iii.c.s"
	cd /d C:\Users\George\Desktop\git_projects\C_plus_plus\DV_HW\cmake-build-debug\1_a_iii && C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\George\Desktop\git_projects\C_plus_plus\DV_HW\1_a_iii\1_a_iii.c -o CMakeFiles\DV_HW_3.dir\1_a_iii.c.s

1_a_iii/CMakeFiles/DV_HW_3.dir/1_a_iii.c.obj.requires:

.PHONY : 1_a_iii/CMakeFiles/DV_HW_3.dir/1_a_iii.c.obj.requires

1_a_iii/CMakeFiles/DV_HW_3.dir/1_a_iii.c.obj.provides: 1_a_iii/CMakeFiles/DV_HW_3.dir/1_a_iii.c.obj.requires
	$(MAKE) -f 1_a_iii\CMakeFiles\DV_HW_3.dir\build.make 1_a_iii/CMakeFiles/DV_HW_3.dir/1_a_iii.c.obj.provides.build
.PHONY : 1_a_iii/CMakeFiles/DV_HW_3.dir/1_a_iii.c.obj.provides

1_a_iii/CMakeFiles/DV_HW_3.dir/1_a_iii.c.obj.provides.build: 1_a_iii/CMakeFiles/DV_HW_3.dir/1_a_iii.c.obj


# Object files for target DV_HW_3
DV_HW_3_OBJECTS = \
"CMakeFiles/DV_HW_3.dir/1_a_iii.c.obj"

# External object files for target DV_HW_3
DV_HW_3_EXTERNAL_OBJECTS =

1_a_iii/DV_HW_3.exe: 1_a_iii/CMakeFiles/DV_HW_3.dir/1_a_iii.c.obj
1_a_iii/DV_HW_3.exe: 1_a_iii/CMakeFiles/DV_HW_3.dir/build.make
1_a_iii/DV_HW_3.exe: 1_a_iii/CMakeFiles/DV_HW_3.dir/linklibs.rsp
1_a_iii/DV_HW_3.exe: 1_a_iii/CMakeFiles/DV_HW_3.dir/objects1.rsp
1_a_iii/DV_HW_3.exe: 1_a_iii/CMakeFiles/DV_HW_3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\George\Desktop\git_projects\C_plus_plus\DV_HW\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable DV_HW_3.exe"
	cd /d C:\Users\George\Desktop\git_projects\C_plus_plus\DV_HW\cmake-build-debug\1_a_iii && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\DV_HW_3.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
1_a_iii/CMakeFiles/DV_HW_3.dir/build: 1_a_iii/DV_HW_3.exe

.PHONY : 1_a_iii/CMakeFiles/DV_HW_3.dir/build

1_a_iii/CMakeFiles/DV_HW_3.dir/requires: 1_a_iii/CMakeFiles/DV_HW_3.dir/1_a_iii.c.obj.requires

.PHONY : 1_a_iii/CMakeFiles/DV_HW_3.dir/requires

1_a_iii/CMakeFiles/DV_HW_3.dir/clean:
	cd /d C:\Users\George\Desktop\git_projects\C_plus_plus\DV_HW\cmake-build-debug\1_a_iii && $(CMAKE_COMMAND) -P CMakeFiles\DV_HW_3.dir\cmake_clean.cmake
.PHONY : 1_a_iii/CMakeFiles/DV_HW_3.dir/clean

1_a_iii/CMakeFiles/DV_HW_3.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\George\Desktop\git_projects\C_plus_plus\DV_HW C:\Users\George\Desktop\git_projects\C_plus_plus\DV_HW\1_a_iii C:\Users\George\Desktop\git_projects\C_plus_plus\DV_HW\cmake-build-debug C:\Users\George\Desktop\git_projects\C_plus_plus\DV_HW\cmake-build-debug\1_a_iii C:\Users\George\Desktop\git_projects\C_plus_plus\DV_HW\cmake-build-debug\1_a_iii\CMakeFiles\DV_HW_3.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : 1_a_iii/CMakeFiles/DV_HW_3.dir/depend

