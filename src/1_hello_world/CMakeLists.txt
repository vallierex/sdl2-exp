# Use the SDL2 from the main project where it's fetched
add_executable(1_hello_world main.cpp)

# Link SDL2 directly without finding the package
target_link_libraries(1_hello_world PRIVATE SDL2::SDL2)
