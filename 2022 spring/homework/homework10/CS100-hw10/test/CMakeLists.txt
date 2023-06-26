add_executable( test_polynomial test_polynomial.cpp )
target_link_libraries( test_polynomial cs100hw10Lib )

add_executable( test_polynomial_function test_polynomial_function.cpp )
target_link_libraries( test_polynomial_function cs100hw10Lib )

add_executable( test_lambda_function test_lambda_function.cpp )
target_link_libraries( test_lambda_function cs100hw10Lib )

#Run unit tests
add_test(unittest_polynomial_1 test_polynomial ${PROJECT_SOURCE_DIR}/data/p1.txt)
add_test(unittest_polynomial_2 test_polynomial ${PROJECT_SOURCE_DIR}/data/p2.txt)

set_tests_properties(unittest_polynomial_1 PROPERTIES PASS_REGULAR_EXPRESSION "2.25")
set_tests_properties(unittest_polynomial_2 PROPERTIES PASS_REGULAR_EXPRESSION "0.75")

add_test(unittest_pol_func_1 test_polynomial_function ${PROJECT_SOURCE_DIR}/data/)

set_tests_properties(unittest_pol_func_1 PROPERTIES PASS_REGULAR_EXPRESSION "3")

add_test(unittest_lambda_func_1 test_lambda_function ${PROJECT_SOURCE_DIR}/data/)

set_tests_properties(unittest_lambda_func_1 PROPERTIES PASS_REGULAR_EXPRESSION "1.6875")