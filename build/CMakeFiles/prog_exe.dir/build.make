# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.28.0/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.28.0/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/zhaoyutainazir/Prog Objet Oriente"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/zhaoyutainazir/Prog Objet Oriente/build"

# Include any dependencies generated for this target.
include CMakeFiles/prog_exe.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/prog_exe.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/prog_exe.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/prog_exe.dir/flags.make

CMakeFiles/prog_exe.dir/main.cpp.o: CMakeFiles/prog_exe.dir/flags.make
CMakeFiles/prog_exe.dir/main.cpp.o: /Users/zhaoyutainazir/Prog\ Objet\ Oriente/main.cpp
CMakeFiles/prog_exe.dir/main.cpp.o: CMakeFiles/prog_exe.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/zhaoyutainazir/Prog Objet Oriente/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/prog_exe.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/prog_exe.dir/main.cpp.o -MF CMakeFiles/prog_exe.dir/main.cpp.o.d -o CMakeFiles/prog_exe.dir/main.cpp.o -c "/Users/zhaoyutainazir/Prog Objet Oriente/main.cpp"

CMakeFiles/prog_exe.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/prog_exe.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/zhaoyutainazir/Prog Objet Oriente/main.cpp" > CMakeFiles/prog_exe.dir/main.cpp.i

CMakeFiles/prog_exe.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/prog_exe.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/zhaoyutainazir/Prog Objet Oriente/main.cpp" -o CMakeFiles/prog_exe.dir/main.cpp.s

# Object files for target prog_exe
prog_exe_OBJECTS = \
"CMakeFiles/prog_exe.dir/main.cpp.o"

# External object files for target prog_exe
prog_exe_EXTERNAL_OBJECTS =

prog_exe: CMakeFiles/prog_exe.dir/main.cpp.o
prog_exe: CMakeFiles/prog_exe.dir/build.make
prog_exe: /usr/local/lib/libtbb.12.11.dylib
prog_exe: mylib_dir/libmesh.a
prog_exe: mylib_dir/libeq.a
prog_exe: mylib_dir/libprob.a
prog_exe: CMakeFiles/prog_exe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="/Users/zhaoyutainazir/Prog Objet Oriente/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable prog_exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/prog_exe.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/prog_exe.dir/build: prog_exe
.PHONY : CMakeFiles/prog_exe.dir/build

CMakeFiles/prog_exe.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/prog_exe.dir/cmake_clean.cmake
.PHONY : CMakeFiles/prog_exe.dir/clean

CMakeFiles/prog_exe.dir/depend:
	cd "/Users/zhaoyutainazir/Prog Objet Oriente/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/zhaoyutainazir/Prog Objet Oriente" "/Users/zhaoyutainazir/Prog Objet Oriente" "/Users/zhaoyutainazir/Prog Objet Oriente/build" "/Users/zhaoyutainazir/Prog Objet Oriente/build" "/Users/zhaoyutainazir/Prog Objet Oriente/build/CMakeFiles/prog_exe.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/prog_exe.dir/depend

