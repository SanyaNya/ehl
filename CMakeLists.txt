cmake_minimum_required(VERSION 3.20)

project(ehl)

#Require C++23 without compiler extensions
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(ehl INTERFACE)
target_include_directories(ehl INTERFACE ${ehl_SOURCE_DIR}/include)

if(BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()
