cmake_minimum_required(VERSION 3.17)
project(course_graph C)

set(CMAKE_C_STANDARD 99)

add_executable(course_graph main.c)

target_include_directories(course_graph PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )