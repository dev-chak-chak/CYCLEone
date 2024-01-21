add_executable(
    action_test
    action_test.cc
)

target_link_libraries(
    action_test PRIVATE
    action module simulator
    GTest::gtest_main
)

gtest_discover_tests(
    action_test
    )

add_executable(
    request_test
    request_test.cc
)

target_link_libraries(
    request_test PRIVATE
    request
    GTest::gtest_main
)

gtest_discover_tests(
    request_test
    )

add_executable(
    response_test
    response_test.cc
)

target_link_libraries(
    response_test PRIVATE
    response
    GTest::gtest_main
)

gtest_discover_tests(
    response_test
    )