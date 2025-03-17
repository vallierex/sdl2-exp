cmake_minimum_required(VERSION 4.0)
project(sdl2_exp)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SDL2
include(FetchContent)
FetchContent_Declare(
        sdl2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-2.32.2
)

# Make SDL2 available
FetchContent_MakeAvailable(sdl2)

# Add the directory where SDL2 provides the CMake config
set(CMAKE_PREFIX_PATH ${sdl2_SOURCE_DIR}/build/cmake)

add_subdirectory(src/1_hello_world)
