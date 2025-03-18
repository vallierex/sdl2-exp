add_executable(5_rendering main.cpp)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)

target_link_libraries(5_rendering PRIVATE $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main> $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>)
target_link_libraries(5_rendering PRIVATE $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>)

# Add resource files
file(GLOB RESOURCE_FILES *.bmp *.png)
set(RESOURCE_FILE_NAMES)
set(RESOURCE_FILES_BINDIR)
foreach (resource_file IN LISTS RESOURCE_FILES)
    get_filename_component(res_file_name ${resource_file} NAME)
    list(APPEND RESOURCE_FILE_NAMES "${res_file_name}")
    set(resource_file_bindir "${CMAKE_CURRENT_BINARY_DIR}/${res_file_name}")
    add_custom_command(OUTPUT "${resource_file_bindir}"
            COMMAND "${CMAKE_COMMAND}" -E copy "${resource_file}" "${resource_file_bindir}"
            DEPENDS "${resource_file}"
    )
    list(APPEND RESOURCE_FILES_BINDIR "${resource_file_bindir}")
endforeach ()
add_custom_target(copy-resources DEPENDS "${RESOURCE_FILES_BINDIR}")
add_dependencies(5_rendering copy-resources)