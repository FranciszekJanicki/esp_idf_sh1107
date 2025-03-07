cmake_minimum_required(VERSION 3.28)

include("$ENV{IDF_PATH}/tools/cmake/project.cmake")

message(STATUS "Building project ${MAKE_PROJECT_NAME}")
message(STATUS "Build for target: ${IDF_BUILD_TARGET}")
message(STATUS "Third-party path: ${THIRD_PARTY_DIR}")
message(STATIS "Nanopb dir: ${NANOPB_DIR}")

if(NOT DEFINED MAKE_PROJECT_NAME)
    SET(MAKE_PROJECT_NAME devcontainer-esp-idf-sh1107)
endif(NOT DEFINED MAKE_PROJECT_NAME)

project(${MAKE_PROJECT_NAME})

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

message("Build type: ${CMAKE_BUILD_TYPE}")

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

