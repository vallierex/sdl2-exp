# Use the SDL2 from the main project where it's fetched
add_executable(2_event_handling_system main.cpp)

# Link SDL2 directly without finding the package
target_link_libraries(2_event_handling_system PRIVATE SDL2::SDL2)
