cmake_minimum_required(VERSION 3.10)
project(course_graph C)

set(CMAKE_C_STANDARD 99)

add_executable(course_graph main.c ArrayList.c LinkedList.c Types.c Test.c
               Department.c Degree.c Parser.c
               )

target_include_directories(course_graph PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )