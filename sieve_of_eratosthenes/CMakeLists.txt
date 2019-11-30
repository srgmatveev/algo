cmake_minimum_required(VERSION 3.15)
project(sieve_of_eratosthenes)

set(CMAKE_CXX_STANDARD 14)

add_executable(sieve_of_eratosthenes main.cpp sieve.h)