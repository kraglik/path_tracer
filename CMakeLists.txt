cmake_minimum_required(VERSION 3.16)
project(path_tracer C)

set(CMAKE_C_STANDARD 11)

add_executable(path_tracer src/main.c)

include_directories(include)
add_subdirectory(src)