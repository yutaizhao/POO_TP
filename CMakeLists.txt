cmake_minimum_required(VERSION 3.10)

# set the project name
project(td)

# enable modern C++
set(CMAKE_CXX_STANDARD 17)

# add the executable
add_executable(prog_exe main.cpp)
add_executable(test_exe test.cpp)

#flags
set(CMAKE_CXX_FLAGS "-fvisibility=hidden")

find_package(TBB)
find_package(Threads)
target_link_libraries(prog_exe Threads::Threads TBB::tbb)
target_link_libraries(test_exe Threads::Threads TBB::tbb)

#指定要访问的子目录
add_subdirectory(mylib_dir)

#mylib要包含的库.h路径
target_include_directories(eq PUBLIC mylib_dir)
target_include_directories(prob PUBLIC mylib_dir)

#prog依赖mylib
target_link_libraries (prog_exe eq prob)
target_link_libraries (test_exe GTest::GTest GTest::Main eq prob)


#ctest : cmake 自带的test
enable_testing()
add_test(prog_test prog_exe 0 2 0.1 0 10 0.1 uniform 0)
find_package(GTest REQUIRED)

#Gtest : 
gtest_discover_tests(test_exe)
