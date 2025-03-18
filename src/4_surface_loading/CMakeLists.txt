add_executable(4_surface_loading main.cpp)

find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)

target_link_libraries(4_surface_loading PRIVATE SDL3::SDL3)
target_link_libraries(4_surface_loading PRIVATE $<IF:$<TARGET_EXISTS:SDL3_image::SDL3_image-shared>,SDL3_image::SDL3_image-shared,SDL3_image::SDL3_image-static>)