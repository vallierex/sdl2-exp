# Use the SDL2 from the main project where it's fetched
add_executable(3_key_press main.cpp)

# Link SDL2 directly without finding the package
target_link_libraries(3_key_press PRIVATE SDL2::SDL2)
