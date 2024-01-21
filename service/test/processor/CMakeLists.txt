add_executable(
    echo_test
    echo_test.cc
)

target_link_libraries(
    echo_test PRIVATE
    echo
    GTest::gtest_main
)

gtest_discover_tests(
    echo_test
    )
