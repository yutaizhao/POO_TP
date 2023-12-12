# CMake generated Testfile for 
# Source directory: /Users/zhaoyutainazir/Prog Objet Oriente
# Build directory: /Users/zhaoyutainazir/Prog Objet Oriente/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
include("/Users/zhaoyutainazir/Prog Objet Oriente/build/test_exe[1]_include.cmake")
add_test(prog_test "prog_exe" "0" "2" "0.1" "0" "10" "0.1" "uniform" "2")
set_tests_properties(prog_test PROPERTIES  _BACKTRACE_TRIPLES "/Users/zhaoyutainazir/Prog Objet Oriente/CMakeLists.txt;35;add_test;/Users/zhaoyutainazir/Prog Objet Oriente/CMakeLists.txt;0;")
subdirs("mylib_dir")
