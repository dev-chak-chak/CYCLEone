# googletest v1.14
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/f8d7d77c06936315286eb55f8de22cd23c188571.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

include(GoogleTest)

add_subdirectory(config)
add_subdirectory(server)
add_subdirectory(message)
add_subdirectory(adapter)
add_subdirectory(network/interface)
add_subdirectory(processor)
add_subdirectory(runner)
