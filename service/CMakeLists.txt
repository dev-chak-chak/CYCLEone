cmake_minimum_required(VERSION 3.14)
project(cycle_on_service)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
find_package(Threads REQUIRED)
find_package(Boost REQUIRED COMPONENTS
             filesystem)

enable_testing()

add_subdirectory(src)
add_subdirectory(test)
