cmake_minimum_required(VERSION 3.15)
project(timsort)

MATH(EXPR stack_size "128 * 1024 * 1024") # 16 Mb
add_executable(timsort main.cpp)
set_target_properties(${MY_PROJECT_NAME}  PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS -Wpedantic -Wall -Wextra --stack ${stack_size}
        )