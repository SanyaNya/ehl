cmake_minimum_required(VERSION 3.20)
project(ehl-examples)

set(CMAKE_CXX_STANDARD 23)
include(cflags.cmake)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

add_executable(quadratic_root quadratic_root.cpp)
