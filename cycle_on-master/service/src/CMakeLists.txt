add_executable(
  service
  service.cpp
)
target_link_libraries(
  service PRIVATE
  server
  tcp_server
  tcp_common
  handler
  json_over_tcp_adapter
  child
  )

FetchContent_Declare(
    json
    URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

add_subdirectory(config)
add_subdirectory(server)
add_subdirectory(message)
add_subdirectory(network/adapter)
add_subdirectory(network/interface/tcp)
add_subdirectory(processor)
add_subdirectory(runner)
