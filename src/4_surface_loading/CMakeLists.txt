# Use the SDL2 from the main project where it's fetched
add_executable(4_surface_loading main.cpp)

# Link SDL2 directly without finding the package
target_link_libraries(4_surface_loading PRIVATE SDL2::SDL2)
