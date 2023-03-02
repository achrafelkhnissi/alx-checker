cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

project(alx-checker
        VERSION 0.1.0
        DESCRIPTION "A checker for alx"
        HOMEPAGE_URL "https://github.com/achrafelkhnissi/alx-checker"
        LANGUAGES CXX)

set(FATAL_ERROR "CMake version 3.24 or higher is required. Download the latest version from https://cmake.org/download/")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -g -std=c++17")
# For Debugging
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g --address-sanitizer")*

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CONFIG_HPP_IN "${PROJECT_SOURCE_DIR}/inc/config.hpp.in")
set(CONFIG_HPP    "${PROJECT_BINARY_DIR}/config.hpp")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# TODO: Remove this after testing
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY /usr/local/bin)

# Disable in-source builds to prevent source tree corruption.
if(" ${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")
  message(FATAL_ERROR "
FATAL: In-source builds are not allowed.
       You should create a separate directory for build files.
")
endif()

# Set the default build type to Release
# cmake -DCMAKE_BUILD_TYPE=Debug -H. -Bbuild/Debug
# cmake -DCMAKE_BUILD_TYPE=Release -H. -Bbuild/Release
if(${CMAKE_BUILD_TYPE} MATCHES Debug)
    message("Debug Build")
elseif(${CMAKE_BUILD_TYPE} MATCHES Release)
    message("Release Build")
endif()
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")


include_directories(${PROJECT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR}/inc)
include_directories(${PROJECT_SOURCE_DIR}/src/checker)
include_directories(${PROJECT_SOURCE_DIR}/src/installer)
include_directories(${PROJECT_SOURCE_DIR}/src/printer)
include_directories(${PROJECT_SOURCE_DIR}/src/animation)

configure_file(${CONFIG_HPP_IN} ${CONFIG_HPP})

add_executable(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/src/main.cpp)

target_sources(${PROJECT_NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}/src/checker/Checker.cpp
        ${CMAKE_SOURCE_DIR}/src/installer/Installer.cpp
        ${CMAKE_SOURCE_DIR}/src/installer/installerUtils.cpp
        ${CMAKE_SOURCE_DIR}/src/installer/installMethods.cpp
        ${CMAKE_SOURCE_DIR}/src/installer/dependencies.cpp
        ${CMAKE_SOURCE_DIR}/src/printer/Printer.cpp
        ${CMAKE_SOURCE_DIR}/src/animation/Animation.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC
                            ${PROJECT_BINARY_DIR}
                            ${PROJECT_SOURCE_DIR}/inc
                            ${PROJECT_SOURCE_DIR}/src/checker
                            ${PROJECT_SOURCE_DIR}/src/installer
                            ${PROJECT_SOURCE_DIR}/src/printer
                            ${PROJECT_SOURCE_DIR}/src/animation)

