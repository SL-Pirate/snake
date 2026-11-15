cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Snake_Server)

file(GLOB SOURCES "src/*.cpp")

find_package(enet REQUIRED)
find_package(glaze REQUIRED)

add_executable(snake_server ${SOURCES})

target_include_directories(snake_server PRIVATE include)

target_link_libraries(snake_server PRIVATE
        enet::enet
        glaze::glaze
)
