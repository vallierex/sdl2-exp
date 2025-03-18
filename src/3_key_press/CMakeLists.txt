add_executable(3_key_press main.cpp)

find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)

target_link_libraries(3_key_press PRIVATE SDL3::SDL3)
target_link_libraries(3_key_press PRIVATE $<IF:$<TARGET_EXISTS:SDL3_image::SDL3_image-shared>,SDL3_image::SDL3_image-shared,SDL3_image::SDL3_image-static>)