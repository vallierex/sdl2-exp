add_executable(2_event_handling_system main.cpp)

find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)

target_link_libraries(2_event_handling_system PRIVATE SDL3::SDL3)
target_link_libraries(2_event_handling_system PRIVATE $<IF:$<TARGET_EXISTS:SDL3_image::SDL3_image-shared>,SDL3_image::SDL3_image-shared,SDL3_image::SDL3_image-static>)