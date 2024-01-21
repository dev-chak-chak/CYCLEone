add_executable(
    adapter_test
    adapter_test.cc
)

target_link_libraries(
    adapter_test PRIVATE
    json_over_tcp_adapter
    nlohmann_json::nlohmann_json
    GTest::gtest_main
)

gtest_discover_tests(
    adapter_test
    )
