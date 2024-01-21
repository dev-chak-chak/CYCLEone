add_library(config OBJECT
            config.hpp)

target_link_libraries(
    config PRIVATE
    )

target_include_directories(
    config PUBLIC
    # /.. is for having parent folder in the include path
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>)

add_library(config_reader OBJECT
    config_reader.cc config_reader.hpp)

target_link_libraries(
    config_reader PRIVATE
    config_json
    )

add_library(
    config_impl OBJECT
    implementation.hpp)

target_include_directories(
    config_impl PUBLIC
    # /.. is for having parent folder in the include path
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>)

add_library(
    config_json OBJECT
    json.cc
    json.hpp)

target_link_libraries(
    config_json PRIVATE
    # Boost::filesystem
    nlohmann_json::nlohmann_json
)

target_include_directories(
    config_json PUBLIC
    # /.. is for having parent folder in the include path
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>)
