cmake_minimum_required(VERSION 3.10)
project(encspot)

if (DEFINED CMAKE_HOST_UNIX)
  add_definitions(-Wall -pedantic -O2 -Wformat -Werror=format-security)
  set(CMAKE_INSTALL_PREFIX "/usr/")
endif()

include_directories ("${PROJECT_SOURCE_DIR}/include")
add_subdirectory(lib)
add_subdirectory(src)
