cmake_minimum_required(VERSION 3.14)
project(Renderer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include headers
include_directories(include)

# Main executable
file(GLOB SRC_FILES "src/*.cpp")
add_executable(renderer ${SRC_FILES})

# Fetch GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

# Tests executable
file(GLOB TEST_FILES "tests/*.cc")
add_executable(vec3_test ${TEST_FILES})
target_include_directories(vec3_test PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(vec3_test gtest_main)

enable_testing()
include(GoogleTest)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
gtest_discover_tests(vec3_test)
