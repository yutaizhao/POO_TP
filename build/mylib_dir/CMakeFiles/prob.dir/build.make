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
include mylib_dir/CMakeFiles/prob.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include mylib_dir/CMakeFiles/prob.dir/compiler_depend.make

# Include the progress variables for this target.
include mylib_dir/CMakeFiles/prob.dir/progress.make

# Include the compile flags for this target's objects.
include mylib_dir/CMakeFiles/prob.dir/flags.make

mylib_dir/CMakeFiles/prob.dir/Problem.cpp.o: mylib_dir/CMakeFiles/prob.dir/flags.make
mylib_dir/CMakeFiles/prob.dir/Problem.cpp.o: /Users/zhaoyutainazir/Prog\ Objet\ Oriente/mylib_dir/Problem.cpp
mylib_dir/CMakeFiles/prob.dir/Problem.cpp.o: mylib_dir/CMakeFiles/prob.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/zhaoyutainazir/Prog Objet Oriente/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object mylib_dir/CMakeFiles/prob.dir/Problem.cpp.o"
	cd "/Users/zhaoyutainazir/Prog Objet Oriente/build/mylib_dir" && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT mylib_dir/CMakeFiles/prob.dir/Problem.cpp.o -MF CMakeFiles/prob.dir/Problem.cpp.o.d -o CMakeFiles/prob.dir/Problem.cpp.o -c "/Users/zhaoyutainazir/Prog Objet Oriente/mylib_dir/Problem.cpp"

mylib_dir/CMakeFiles/prob.dir/Problem.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/prob.dir/Problem.cpp.i"
	cd "/Users/zhaoyutainazir/Prog Objet Oriente/build/mylib_dir" && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/zhaoyutainazir/Prog Objet Oriente/mylib_dir/Problem.cpp" > CMakeFiles/prob.dir/Problem.cpp.i

mylib_dir/CMakeFiles/prob.dir/Problem.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/prob.dir/Problem.cpp.s"
	cd "/Users/zhaoyutainazir/Prog Objet Oriente/build/mylib_dir" && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/zhaoyutainazir/Prog Objet Oriente/mylib_dir/Problem.cpp" -o CMakeFiles/prob.dir/Problem.cpp.s

# Object files for target prob
prob_OBJECTS = \
"CMakeFiles/prob.dir/Problem.cpp.o"

# External object files for target prob
prob_EXTERNAL_OBJECTS =

mylib_dir/libprob.a: mylib_dir/CMakeFiles/prob.dir/Problem.cpp.o
mylib_dir/libprob.a: mylib_dir/CMakeFiles/prob.dir/build.make
mylib_dir/libprob.a: mylib_dir/CMakeFiles/prob.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="/Users/zhaoyutainazir/Prog Objet Oriente/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libprob.a"
	cd "/Users/zhaoyutainazir/Prog Objet Oriente/build/mylib_dir" && $(CMAKE_COMMAND) -P CMakeFiles/prob.dir/cmake_clean_target.cmake
	cd "/Users/zhaoyutainazir/Prog Objet Oriente/build/mylib_dir" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/prob.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
mylib_dir/CMakeFiles/prob.dir/build: mylib_dir/libprob.a
.PHONY : mylib_dir/CMakeFiles/prob.dir/build

mylib_dir/CMakeFiles/prob.dir/clean:
	cd "/Users/zhaoyutainazir/Prog Objet Oriente/build/mylib_dir" && $(CMAKE_COMMAND) -P CMakeFiles/prob.dir/cmake_clean.cmake
.PHONY : mylib_dir/CMakeFiles/prob.dir/clean

mylib_dir/CMakeFiles/prob.dir/depend:
	cd "/Users/zhaoyutainazir/Prog Objet Oriente/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/zhaoyutainazir/Prog Objet Oriente" "/Users/zhaoyutainazir/Prog Objet Oriente/mylib_dir" "/Users/zhaoyutainazir/Prog Objet Oriente/build" "/Users/zhaoyutainazir/Prog Objet Oriente/build/mylib_dir" "/Users/zhaoyutainazir/Prog Objet Oriente/build/mylib_dir/CMakeFiles/prob.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : mylib_dir/CMakeFiles/prob.dir/depend

