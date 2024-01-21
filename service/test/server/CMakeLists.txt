add_executable(
    server_test
    server_test.cc
)

target_link_libraries(
    server_test PRIVATE
    server
    tcp_server
    tcp_common
    handler
    json_over_tcp_adapter
    child
    GTest::gtest_main
)

gtest_discover_tests(server_test)
