add_executable(
    tcp_test
    tcp_test.cc
)

target_link_libraries(
    tcp_test PRIVATE
    tcp_common
    echo
    tcp_server
    tcp_client
    GTest::gtest_main
)

gtest_discover_tests(
    tcp_test
    )
