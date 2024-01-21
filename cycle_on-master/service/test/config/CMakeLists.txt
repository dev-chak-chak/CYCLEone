add_executable(
    config_test
    config_test.cc
)

target_link_libraries(
    config_test PRIVATE
    config_reader
    config_json
    GTest::gtest_main
    Boost::filesystem
    nlohmann_json::nlohmann_json
)

gtest_discover_tests(
    config_test
    )

file(
    COPY ${CMAKE_CURRENT_SOURCE_DIR}/../data/config_test.json
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
