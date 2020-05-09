cmake_minimum_required(VERSION 3.13)
project(nearestPoints)

add_definitions(-std=c++17)
add_definitions(-D_GLIBCXX_DEBUG)

file(GLOB SOURCE_FILES src/*.cpp)
add_library(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_subdirectory(lib/googletest)
add_subdirectory(test)
