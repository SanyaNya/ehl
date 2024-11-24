include(cflags.cmake)

add_executable(quadratic_root quadratic_root.cpp)
target_link_libraries(quadratic_root ehl)
