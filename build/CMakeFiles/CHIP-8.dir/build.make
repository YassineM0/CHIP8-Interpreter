# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.30

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\mingw64\bin\cmake.exe

# The command to remove a file.
RM = C:\mingw64\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\yassi\source\repos\chip-8

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\yassi\source\repos\chip-8\build

# Include any dependencies generated for this target.
include CMakeFiles/CHIP-8.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/CHIP-8.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/CHIP-8.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CHIP-8.dir/flags.make

CMakeFiles/CHIP-8.dir/source/main.cpp.obj: CMakeFiles/CHIP-8.dir/flags.make
CMakeFiles/CHIP-8.dir/source/main.cpp.obj: CMakeFiles/CHIP-8.dir/includes_CXX.rsp
CMakeFiles/CHIP-8.dir/source/main.cpp.obj: C:/Users/yassi/source/repos/chip-8/source/main.cpp
CMakeFiles/CHIP-8.dir/source/main.cpp.obj: CMakeFiles/CHIP-8.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\yassi\source\repos\chip-8\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/CHIP-8.dir/source/main.cpp.obj"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CHIP-8.dir/source/main.cpp.obj -MF CMakeFiles\CHIP-8.dir\source\main.cpp.obj.d -o CMakeFiles\CHIP-8.dir\source\main.cpp.obj -c C:\Users\yassi\source\repos\chip-8\source\main.cpp

CMakeFiles/CHIP-8.dir/source/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/CHIP-8.dir/source/main.cpp.i"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\yassi\source\repos\chip-8\source\main.cpp > CMakeFiles\CHIP-8.dir\source\main.cpp.i

CMakeFiles/CHIP-8.dir/source/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/CHIP-8.dir/source/main.cpp.s"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\yassi\source\repos\chip-8\source\main.cpp -o CMakeFiles\CHIP-8.dir\source\main.cpp.s

# Object files for target CHIP-8
CHIP__8_OBJECTS = \
"CMakeFiles/CHIP-8.dir/source/main.cpp.obj"

# External object files for target CHIP-8
CHIP__8_EXTERNAL_OBJECTS =

CHIP-8.exe: CMakeFiles/CHIP-8.dir/source/main.cpp.obj
CHIP-8.exe: CMakeFiles/CHIP-8.dir/build.make
CHIP-8.exe: libLibsModule.a
CHIP-8.exe: CMakeFiles/CHIP-8.dir/linkLibs.rsp
CHIP-8.exe: CMakeFiles/CHIP-8.dir/objects1.rsp
CHIP-8.exe: CMakeFiles/CHIP-8.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\yassi\source\repos\chip-8\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable CHIP-8.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\CHIP-8.dir\link.txt --verbose=$(VERBOSE)
	C:\mingw64\bin\cmake.exe -E copy_if_different C:/Users/yassi/source/repos/chip-8/dependencies/SDL/lib/SDL2.dll C:/Users/yassi/source/repos/chip-8/build

# Rule to build all files generated by this target.
CMakeFiles/CHIP-8.dir/build: CHIP-8.exe
.PHONY : CMakeFiles/CHIP-8.dir/build

CMakeFiles/CHIP-8.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\CHIP-8.dir\cmake_clean.cmake
.PHONY : CMakeFiles/CHIP-8.dir/clean

CMakeFiles/CHIP-8.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\yassi\source\repos\chip-8 C:\Users\yassi\source\repos\chip-8 C:\Users\yassi\source\repos\chip-8\build C:\Users\yassi\source\repos\chip-8\build C:\Users\yassi\source\repos\chip-8\build\CMakeFiles\CHIP-8.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/CHIP-8.dir/depend

