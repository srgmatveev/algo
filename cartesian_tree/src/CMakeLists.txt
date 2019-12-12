cmake_minimum_required(VERSION 3.15)
project(cartesian_tree)

add_executable(${CMAKE_PROJECT_NAME} main.cpp )
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS -Wpedantic -Wall -Wextra
        )