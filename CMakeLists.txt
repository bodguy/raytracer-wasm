cmake_minimum_required(VERSION 3.16)
project(Raytracer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
set(THIRDPARTY_DIR "${CMAKE_SOURCE_DIR}/stb")

add_executable(${PROJECT_NAME})
file(GLOB_RECURSE RAYTRACER_SOURCE_FILES
        "${SOURCE_DIR}/*.h"
        "${SOURCE_DIR}/*.cpp")
target_sources(${PROJECT_NAME}
        PRIVATE
        ${RAYTRACER_SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ${THIRDPARTY_DIR})