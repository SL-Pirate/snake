cmake_minimum_required(VERSION 3.24)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Snake)

include(cmake/CMakeRC.cmake)
file(GLOB SOURCES "src/*.cpp")
file(GLOB_RECURSE RES_FILES CONFIGURE_DEPENDS "res/*")

find_package(wxWidgets COMPONENTS core base REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

add_executable(snake ${SOURCES})

target_include_directories(snake PRIVATE include)

cmrc_add_resource_library(snake_res NAMESPACE res WHENCE res ${RES_FILES})

target_link_libraries(snake PRIVATE
        SDL2::SDL2main
        SDL2_image::SDL2_image
        sdl_ttf::sdl_ttf
        SDL2_mixer::SDL2_mixer
        wxWidgets::wxWidgets
        snake_res
)

if (CMAKE_SYSTEM_NAME STREQUAL "FreeBSD")
    target_link_libraries(snake PRIVATE usb usbhid)
endif ()
