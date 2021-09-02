cmake_minimum_required(VERSION 3.10)

project(devlib LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# The library target
file(GLOB SOURCE_FILES *.cpp)
add_library(devlib SHARED ${SOURCE_FILES})
target_compile_definitions(devlib PRIVATE DEVLIB_LIBRARY)

# Dependencies
find_package(Qt5 COMPONENTS Core REQUIRED)
target_link_libraries(devlib Qt5::Core)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

