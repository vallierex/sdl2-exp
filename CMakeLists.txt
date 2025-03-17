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
FetchContent_MakeAvailable(sdl2)

add_executable(sdl2_exp src/main.cpp)

# Link the SDL2 library to the executable
target_link_libraries(sdl2_exp PRIVATE SDL2::SDL2)

# Include the SDL2 headers
target_include_directories(sdl2_exp PUBLIC ${sdl2_SOURCE_DIR}/include)
