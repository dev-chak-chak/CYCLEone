add_library(action OBJECT
            action.hpp)

target_include_directories(
    action PUBLIC
    # /.. is for having parent folder in the include path
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>)

add_library(module OBJECT
            module.hpp)

target_include_directories(
    module PUBLIC
    # /.. is for having parent folder in the include path
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>)

add_library(simulator OBJECT
            simulator.hpp)

target_include_directories(
    simulator PUBLIC
    # /.. is for having parent folder in the include path
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>)

add_library(request OBJECT
            request.hpp)

target_include_directories(
    request PUBLIC
    # /.. is for having parent folder in the include path
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>)

add_library(response OBJECT
            response.hpp)

target_include_directories(
    response PUBLIC
    # /.. is for having parent folder in the include path
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>)