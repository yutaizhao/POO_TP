if(EXISTS "/Users/zhaoyutainazir/Prog Objet Oriente/test_exe[1]_tests.cmake")
  include("/Users/zhaoyutainazir/Prog Objet Oriente/test_exe[1]_tests.cmake")
else()
  add_test(test_exe_NOT_BUILT test_exe_NOT_BUILT)
endif()
