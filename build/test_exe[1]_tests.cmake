add_test([=[UnitaryTest.MeshTest]=]  [==[/Users/zhaoyutainazir/Prog Objet Oriente/build/test_exe]==] [==[--gtest_filter=UnitaryTest.MeshTest]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UnitaryTest.MeshTest]=]  PROPERTIES WORKING_DIRECTORY [==[/Users/zhaoyutainazir/Prog Objet Oriente/build]==] SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[UnitaryTest.ProblemTest]=]  [==[/Users/zhaoyutainazir/Prog Objet Oriente/build/test_exe]==] [==[--gtest_filter=UnitaryTest.ProblemTest]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UnitaryTest.ProblemTest]=]  PROPERTIES WORKING_DIRECTORY [==[/Users/zhaoyutainazir/Prog Objet Oriente/build]==] SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[UnitaryTest.VariableTest]=]  [==[/Users/zhaoyutainazir/Prog Objet Oriente/build/test_exe]==] [==[--gtest_filter=UnitaryTest.VariableTest]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UnitaryTest.VariableTest]=]  PROPERTIES WORKING_DIRECTORY [==[/Users/zhaoyutainazir/Prog Objet Oriente/build]==] SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[MainFunctionTest.EquationTest]=]  [==[/Users/zhaoyutainazir/Prog Objet Oriente/build/test_exe]==] [==[--gtest_filter=MainFunctionTest.EquationTest]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MainFunctionTest.EquationTest]=]  PROPERTIES WORKING_DIRECTORY [==[/Users/zhaoyutainazir/Prog Objet Oriente/build]==] SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  test_exe_TESTS UnitaryTest.MeshTest UnitaryTest.ProblemTest UnitaryTest.VariableTest MainFunctionTest.EquationTest)
