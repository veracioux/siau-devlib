cmake_minimum_required(VERSION 3.10)
project(devlib_tests LANGUAGES CXX)

# Configuration
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(LIB_DEPENDENCIES devlib Qt5::Core Qt5::Test)

# Find QtTest library
find_package(Qt5 COMPONENTS Core Test REQUIRED)
# Build devlib
add_subdirectory(../ ${CMAKE_CURRENT_BINARY_DIR}/devlib)

include_directories(../)

enable_testing()
add_test(Test_ValueSpec test_valuespec)
add_test(Test_JSON      test_json)
add_test(Test_Function  test_function)

add_executable(test_valuespec valuespec.cpp)
add_executable(test_function  function.cpp)
add_executable(test_json      json.cpp)

target_link_libraries(test_valuespec ${LIB_DEPENDENCIES})
target_link_libraries(test_function  ${LIB_DEPENDENCIES})
target_link_libraries(test_json      ${LIB_DEPENDENCIES})

