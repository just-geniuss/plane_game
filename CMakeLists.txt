cmake_minimum_required(VERSION 3.16)

project(Spaceshooter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Option to build with static linking
option(BUILD_STATIC "Build with static linking" ON)

# Set static linking preference
if(BUILD_STATIC)
    set(SFML_STATIC_LIBRARIES TRUE)
    if(WIN32)
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    endif()
endif()

find_package(SFML 3 QUIET COMPONENTS Graphics Window System Audio)
if(NOT SFML_FOUND)
    find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system audio)
endif()

file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
    "src/*.cpp"
)

add_executable(spaceshooter ${PROJECT_SOURCES})

target_include_directories(spaceshooter PRIVATE include)

if(TARGET SFML::Graphics)
    target_link_libraries(spaceshooter PRIVATE SFML::Graphics SFML::Window SFML::System SFML::Audio)
else()
    target_link_libraries(spaceshooter PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)
endif()

# Link static dependencies for SFML on different platforms
if(BUILD_STATIC)
    if(WIN32)
        target_link_libraries(spaceshooter PRIVATE winmm opengl32)
        if(MSVC)
            target_link_libraries(spaceshooter PRIVATE gdi32)
        endif()
    elseif(UNIX AND NOT APPLE)
        target_link_libraries(spaceshooter PRIVATE X11 Xrandr Xcursor Xi GL pthread udev)
    elseif(APPLE)
        find_library(COREFOUNDATION_LIBRARY CoreFoundation)
        find_library(COCOA_LIBRARY Cocoa)
        find_library(IOKIT_LIBRARY IOKit)
        find_library(COREAUDIO_LIBRARY CoreAudio)
        find_library(AUDIOTOOLBOX_LIBRARY AudioToolbox)
        find_library(COREVIDEO_LIBRARY CoreVideo)
        find_library(OPENGL_LIBRARY OpenGL)
        target_link_libraries(spaceshooter PRIVATE 
            ${COREFOUNDATION_LIBRARY}
            ${COCOA_LIBRARY}
            ${IOKIT_LIBRARY}
            ${COREAUDIO_LIBRARY}
            ${AUDIOTOOLBOX_LIBRARY}
            ${COREVIDEO_LIBRARY}
            ${OPENGL_LIBRARY}
        )
    endif()
endif()

# Copy assets to build directory
add_custom_command(TARGET spaceshooter POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:spaceshooter>/assets
)
