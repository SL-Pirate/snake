cmake_minimum_required(VERSION 3.24)

project(Snake)

file(GLOB SOURCES "src/*.cpp")

set(VALID FALSE)

#WINDOWS
if(WIN32)
message(WARNING "Building for Windows")
message(STATUS "Looking for a valid installation of wxWidgets")

# Add the path_to_wxWidgets_installation_folder to your environment variables under the name "wxWidgets"
set(wxWidgets_ROOT_DIR $ENV{wxWidgets})

# change the wxWidgets configuration
set(wxWidgets_CONFIGURATION mswu)

# Add the path_to_SDL2_installation_folder to your environment variables under the name "SDL2"
# NOTE: Please save SDL2, SDL2_image and SDL2_ttf under this folder.
# SDL2.
# ├───SDL2
# ├───SDL2_image
# ├───SDL2_mixer
# ├───SDL2_ttf
set(SDL2_ROOT_DIR $ENV{SDL2})

find_package(wxWidgets COMPONENTS core base gl aui richtext REQUIRED)
if(wxWidgets_FOUND)
message(STATUS "Found wxWidgets.\nLooking for a valid installation of SDL2")
set(VALID TRUE)
else()
message(ERROR "wxWidgets not found")
endif()

set(SDL2_DIR ${SDL2_ROOT_DIR}/SDL2/cmake)
set(SDL2_image_DIR ${SDL2_ROOT_DIR}/SDL2_image/cmake)
set(SDL2_ttf_DIR ${SDL2_ROOT_DIR}/SDL2_ttf/cmake)
set(SDL2_mixer_DIR ${SDL2_ROOT_DIR}/SDL2_mixer/cmake)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
find_package(SDL2_mixer CONFIG REQUIRED)

if(SDL2_FOUND)
message(STATUS "Found SDL2.\nLooking for a valid installation of SDL2_image")
else()
set(VALID FALSE)
message(ERROR "SDL2 not found")
endif()

if(SDL2_image_FOUND)
message(STATUS "Found SDL2_image.\nLooking for a valid installation of SDL2_mixer")
else()
set(VALID FALSE)
message(ERROR "SDL2_image not found")
endif()

if(SDL2_mixer_FOUND)
message(STATUS "Found SDL2_mixer.\nLooking for a valid installation of SDL2_ttf")
else()
set(VALID FALSE)
message(ERROR "SDL2_mixer not found")
endif()

if(SDL2_ttf_FOUND)
message(STATUS "Found SDL2_ttf")
else()
set(VALID FALSE)
message(ERROR "SDL2_ttf not found")
endif()

if(VALID)
message(STATUS "Sources Ready!")
include(${wxWidgets_USE_FILE})
include_directories(include ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS} ${SDL2MIXER_INCLUDE_DIRS})

message(STATUS "Adding icon")
set(APP_ICON ${CMAKE_CURRENT_SOURCE_DIR}/res/icon.rc)

add_executable(snake ${SOURCES} ${APP_ICON})
set_property(TARGET snake PROPERTY CXX_STANDARD 17)
target_link_libraries(
    snake 
    ${SDL2_LIBRARIES} 
    $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>  
    $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static> 
    $<IF:$<TARGET_EXISTS:SDL2_mixer::SDL2_mixer>,SDL2_mixer::SDL2_mixer,SDL2_mixer::SDL2_mixer-static> 
    ${wxWidgets_LIBRARIES}
)

message(STATUS "Setting up resource files")
add_custom_command(TARGET snake PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/res/ $<TARGET_FILE_DIR:snake>/res/)

message(STATUS "Setting up dynamic libraries")
message(STATUS "SDL2IMAGEBin: " ${_sdl2image_dll})
add_custom_command(TARGET snake PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_ROOT_DIR}/SDL2/lib/x86/SDL2.dll $<TARGET_FILE_DIR:snake>)
add_custom_command(TARGET snake PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_ROOT_DIR}/SDL2_image/lib/x86/SDL2_image.dll $<TARGET_FILE_DIR:snake>)
add_custom_command(TARGET snake PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_ROOT_DIR}/SDL2_ttf/lib/x86/SDL2_ttf.dll $<TARGET_FILE_DIR:snake>)
add_custom_command(TARGET snake PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_ROOT_DIR}/SDL2_mixer/lib/x86/SDL2_mixer.dll $<TARGET_FILE_DIR:snake>)
endif()


#_____________________________________________________________________________________________________________________________________#

#UNIX / LINUX
elseif(UNIX)

message(WARNING "Configuring for Linux/Unix")
message(STATUS "Looking for a valid installation of wxWidgets")
find_package(wxWidgets COMPONENTS core base REQUIRED)
if(wxWidgets_FOUND)
message(STATUS "Found wxWidgets.\nLooking for a valid installation of SDL2")
set(VALID TRUE)
else()
message(ERROR "wxWidgets not found")
endif()

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image)
PKG_SEARCH_MODULE(SDL2TTF REQUIRE SDL2_ttf)
PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer)

if(SDL2_FOUND)
message(STATUS "Found SDL2.\nLooking for a valid installation of SDL2_image")
else()
set(VALID FALSE)
message(ERROR "SDL2 not found")
endif()

if(SDL2IMAGE_FOUND)
message(STATUS "Found SDL2_image.\nLooking for a valid installation of SDL2_ttf")
else()
set(VALID FALSE)
message(ERROR "SDL2_image not found")
endif()

if(SDL2TTF_FOUND)
message(STATUS "Found SDL2_mixer.\nLooking for a valid installation of SDL2_mixer")
else()
set(VALID FALSE)
message(ERROR "SDL2_ttf not found")
endif()

if(SDL2MIXER_FOUND)
message(STATUS "Found SDL2_mixer")
else()
set(VALID FALSE)
message(ERROR "SDL2_mixer not found")
endif()

if(VALID)
message(STATUS "Sources Ready!")

include(${wxWidgets_USE_FILE})
include_directories(include ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS} ${SDL2MIXER_INCLUDE_DIRS})

add_executable(snake ${SOURCES})
target_link_libraries(snake ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES} ${SDL2MIXER_LIBRARIES} ${wxWidgets_LIBRARIES})

message(STATUS "Setting up resource files")
add_custom_command(TARGET snake PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/res/ $<TARGET_FILE_DIR:snake>/res/)

endif()
endif()