cmake_minimum_required(VERSION 3.15)
project(timsort)
find_package(Threads REQUIRED)
MATH(EXPR stack_size "128 * 1024 * 1024") # 16 Mb
add_executable(${CMAKE_PROJECT_NAME} main.cpp)
set_target_properties(${CMAKE_PROJECT_NAME}  PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS -Wpedantic -Wall -Wextra --stack ${stack_size}
        )
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
target_link_libraries(${CMAKE_PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})