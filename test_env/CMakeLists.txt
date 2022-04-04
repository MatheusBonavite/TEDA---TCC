cmake_minimum_required(VERSION 3.21)
project(test_env)

set(CMAKE_C_STANDARD 11)

add_subdirectory(EuclideanDistance)

add_executable(test_env main.c)
