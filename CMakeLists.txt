cmake_minimum_required(VERSION 3.24)

project(Snake)

file(GLOB SOURCES "src/*.cpp")

find_package(wxWidgets COMPONENTS core base REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

add_executable(snake ${SOURCES})

target_include_directories(snake PRIVATE include)

target_link_libraries(snake PRIVATE
    SDL2::SDL2main
    SDL2_image::SDL2_image
    sdl_ttf::sdl_ttf
    SDL2_mixer::SDL2_mixer
    wxWidgets::wxWidgets
)

add_custom_command(TARGET snake POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res/ $<TARGET_FILE_DIR:snake>/res/)
