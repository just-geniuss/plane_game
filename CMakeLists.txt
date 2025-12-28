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

if(APPLE)
    # Allow finding SFML installed via Homebrew when CMAKE_PREFIX_PATH is not set
    find_library(COREFOUNDATION_LIBRARY CoreFoundation)
    target_link_libraries(spaceshooter PRIVATE ${COREFOUNDATION_LIBRARY})
endif()
