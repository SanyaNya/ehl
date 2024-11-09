cmake_minimum_required(VERSION 3.19)

project(ehl)

add_library(ehl INTERFACE)
target_include_directories(ehl INTERFACE ${ehl_SOURCE_DIR})
