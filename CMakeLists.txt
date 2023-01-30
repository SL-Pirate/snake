cmake_minimum_required(VERSION 3.24)

project(Snake)

file(GLOB SOURCES "src/*.cpp")

if(WIN32)

set(wxWidgets_ROOT_DIR $ENV{wxWidgets})
set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets COMPONENTS core base gl aui richtext REQUIRED)

set(SDL2_ROOT_DIR $ENV{SDL2})
set(SDL2_DIR ${SDL2_ROOT_DIR}/cmake)
# set(SDL2_image_DIR ${SDL2_ROOT_DIR}/cmake)
# set(SDL2_ttf_DIR ${SDL2_ROOT_DIR}/cmake)
find_package(SDL2 REQUIRED)
# find_package(SDL2_image REQUIRED)
# find_package(SDL2_ttf REQUIRED)
set(SDL2IMAGE_LIBRARIES ${SDL2_ROOT_DIR}/lib/x86/SDL2_image.lib)
set(SDL2TTF_LIBRARIES ${SDL2_ROOT_DIR}/lib/x86/SDL2_ttf.lib)

include(${wxWidgets_USE_FILE})
include_directories(include ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})

add_executable(snake ${SOURCES})
target_link_libraries(snake ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES} ${wxWidgets_LIBRARIES})

# adding res
# target_sources(res ${CMAKE_CURRENT_SOURCE_DIR}/res/icon.rc)
SET(LINKFLAGS ${CMAKE_CURRENT_SOURCE_DIR}/res/icon.res)
SET_TARGET_PROPERTIES(snake PROPERTIES LINK_FLAGS ${LINKFLAGS})

elseif(UNIX)
find_package(wxWidgets COMPONENTS core base REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image)
PKG_SEARCH_MODULE(SDL2TTF REQUIRE SDL2_ttf)

include(${wxWidgets_USE_FILE})
include_directories(include ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})

add_executable(snake ${SOURCES})
target_link_libraries(snake ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES} ${wxWidgets_LIBRARIES})

endif()