add_executable(
    fake_module_test
    fake_test.cc
)

target_link_libraries(
    fake_module_test PRIVATE
    fake
    GTest::gtest_main
)

gtest_discover_tests(fake_module_test)

add_executable(
    child_module_test
    child_test.cc
)

target_link_libraries(
    child_module_test PRIVATE
    child
    GTest::gtest_main
)

gtest_discover_tests(child_module_test)
