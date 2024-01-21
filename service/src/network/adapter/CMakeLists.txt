add_library(
    adapter OBJECT
    adapter.hpp)

target_include_directories(
    adapter PUBLIC
    # /.. is for having parent folder in the include path
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../..>)

add_library(
    json_over_tcp_adapter OBJECT
    json_over_tcp.hpp json_over_tcp.cc)

target_link_libraries(
    json_over_tcp_adapter PRIVATE
    nlohmann_json::nlohmann_json
)

target_include_directories(
    json_over_tcp_adapter PUBLIC
    # /.. is for having parent folder in the include path
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../..>)
