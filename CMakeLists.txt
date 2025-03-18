cmake_minimum_required(VERSION 4.0)
project(sdl2_exp)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src/1_hello_world)
add_subdirectory(src/2_event_handling_system)
add_subdirectory(src/3_key_press)
add_subdirectory(src/4_surface_loading)
add_subdirectory(src/5_rendering)