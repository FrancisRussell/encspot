cmake_minimum_required(VERSION 2.8)
project(encspot)

if (DEFINED CMAKE_HOST_UNIX)
  add_definitions(-Wall -pedantic)
endif()

include_directories ("${PROJECT_SOURCE_DIR}/include")
add_subdirectory(lib)
add_subdirectory(src)
