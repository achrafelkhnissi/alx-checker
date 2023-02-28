cmake_minimum_required(VERSION 3.0 FATAL_ERROR "CMake 3.0 or higher is required")

project(alx-checker
        VERSION 0.1.0
        DESCRIPTION "A checker for alx"
        HOMEPAGE_URL "https://github.com/achrafelkhnissi/CMake-Playground"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} main.cpp)

configure_file(${PROJECT_SOURCE_DIR}/config.h.in ${PROJECT_BINARY_DIR}/config.h)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})
