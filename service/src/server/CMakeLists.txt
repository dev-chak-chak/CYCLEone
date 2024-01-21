add_library(server OBJECT
            server.cc server.hpp)

target_link_libraries(
    server PRIVATE
    tcp_server
    handler
    nlohmann_json::nlohmann_json
    Threads::Threads
    )

target_include_directories(
    server PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
