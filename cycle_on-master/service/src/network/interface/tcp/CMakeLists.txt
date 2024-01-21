add_library(
    tcp_common OBJECT
    common.cc
    common.hpp)

target_link_libraries(
    tcp_common PRIVATE 
    )

target_include_directories(
    tcp_common PUBLIC
    # /.. is for having parent folder in the include path
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../..>)

add_library(
    tcp_server OBJECT
    server.cc
    server.hpp)

target_link_libraries(
    tcp_server PRIVATE 
    tcp_common
    echo)

target_include_directories(
    tcp_server PUBLIC
    # /.. is for having parent folder in the include path
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../..>)

add_library(
    tcp_client OBJECT
    client.cc
    client.hpp)

target_link_libraries(
    tcp_client PRIVATE 
    tcp_common)

target_include_directories(
    tcp_client PUBLIC
    # /.. is for having parent folder in the include path
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../..>)
