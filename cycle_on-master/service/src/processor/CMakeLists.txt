add_library(
    processor OBJECT
    processor.hpp)

target_include_directories(
    processor PUBLIC
    # /.. is for having parent folder in the include path
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>)

add_library(
    echo OBJECT
    echo.cc
    echo.hpp)

target_include_directories(
    echo PUBLIC
    # /.. is for having parent folder in the include path
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>)

add_library(
    handler OBJECT
    handler.cc
    handler.hpp)

target_link_libraries(
    handler PRIVATE
    runner_module
    json_over_tcp_adapter
    nlohmann_json::nlohmann_json
)

target_include_directories(
    handler PUBLIC
    # /.. is for having parent folder in the include path
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>)