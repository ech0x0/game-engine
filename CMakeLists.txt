cmake_minimum_required(VERSION 3.24)

if (WIN32)
set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")
else()
set(CMAKE_TOOLCHAIN_FILE "/opt/vcpkg/scripts/buildsystems/vcpkg.cmake")
endif()

set(CMAKE_VERBOSE_MAKEFILE ON)

project(game-engine VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(game-engine ${SRC_FILES})

if(MSVC)
target_compile_options(game-engine PRIVATE /W4)
target_link_options(game-engine PRIVATE /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup)
else()
target_compile_options(game-engine PRIVATE -Wall -Wextra -Wpedantic)
endif()

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(game-engine PRIVATE glfw)

find_package(GLEW CONFIG REQUIRED)
target_link_libraries(game-engine PRIVATE GLEW::GLEW)