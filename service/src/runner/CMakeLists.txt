add_library(
    runner_module OBJECT
    module.hpp)

target_include_directories(
    runner_module PUBLIC
    # /.. is for having parent folder in the include path
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>)

add_library(
    fake OBJECT
    fake.cc
    fake.hpp)

target_include_directories(
    fake PUBLIC
    # /.. is for having parent folder in the include path
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>)

add_library(
    child OBJECT
    child.cc
    child.hpp)

target_link_libraries(
    child PRIVATE 
    )

target_include_directories(
    child PUBLIC
    # /.. is for having parent folder in the include path
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>)
