cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

project(alx-checker
        VERSION 0.1.0
        DESCRIPTION "A checker for alx"
        HOMEPAGE_URL "https://github.com/achrafelkhnissi/CMake-Playground"
        LANGUAGES CXX)

set(FATAL_ERROR "CMake version 3.24 or higher is required. Download the latest version from https://cmake.org/download/")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}) -Wall -Wextra -Werror -std=c++17")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CONFIG_HPP_IN "${PROJECT_SOURCE_DIR}/inc/config.hpp.in")
set(CONFIG_HPP    "${PROJECT_BINARY_DIR}/config.hpp")
set(CMAKE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(SOURCES ${CMAKE_SRC}/main.cpp
           ${CMAKE_SRC}/checker/Checker.cpp
           ${CMAKE_SRC}/installer/Installer.cpp
           ${CMAKE_SRC}/installer/installerUtils.cpp
           ${CMAKE_SRC}/installer/installMethods.cpp
           ${CMAKE_SRC}/installer/dependencies.cpp
           ${CMAKE_SRC}/printer/Printer.cpp
           ${CMAKE_SRC}/animation/Animation.cpp)

include_directories(${PROJECT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR}/inc)
include_directories(${PROJECT_SOURCE_DIR}/src/checker)
include_directories(${PROJECT_SOURCE_DIR}/src/installer)
include_directories(${PROJECT_SOURCE_DIR}/src/printer)
include_directories(${PROJECT_SOURCE_DIR}/src/animation)

message(STATUS "CMAKE_PROJECT_VERSION: ${CMAKE_PROJECT_VERSION}")

configure_file(${CONFIG_HPP_IN} ${CONFIG_HPP})

#add_executable(${PROJECT_NAME} ${SOURCES})

add_executable(${PROJECT_NAME}
                ${CMAKE_SOURCE_DIR}/main.cpp
                ${CMAKE_SOURCE_DIR}/checker/Checker.cpp
                ${CMAKE_SOURCE_DIR}/installer/Installer.cpp
                ${CMAKE_SOURCE_DIR}/installer/installerUtils.cpp
                ${CMAKE_SOURCE_DIR}/installer/installMethods.cpp
                ${CMAKE_SOURCE_DIR}/installer/dependencies.cpp
                ${CMAKE_SOURCE_DIR}/printer/Printer.cpp
                ${CMAKE_SOURCE_DIR}/animation/Animation.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC
                            ${PROJECT_BINARY_DIR}
                            ${PROJECT_SOURCE_DIR}/inc
                            ${PROJECT_SOURCE_DIR}/src/checker
                            ${PROJECT_SOURCE_DIR}/src/installer
                            ${PROJECT_SOURCE_DIR}/src/printer
                            ${PROJECT_SOURCE_DIR}/src/animation)
