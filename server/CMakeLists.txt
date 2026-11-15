cmake_minimum_required(VERSION 3.24)

project(Snake_Server)

file(GLOB SOURCES "src/*.cpp")

find_package(enet REQUIRED)

add_executable(snake_server ${SOURCES})

target_include_directories(snake_server PRIVATE include)

target_link_libraries(snake_server PRIVATE
        enet::enet
)
