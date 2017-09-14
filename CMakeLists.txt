cmake_minimum_required(VERSION 3.7)
project(minishell)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c)
add_executable(minishell ${SOURCE_FILES})