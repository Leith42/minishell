cmake_minimum_required(VERSION 3.7)
set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES
        src/main.c
        )

add_executable(minishell ${SOURCE_FILES})

include_directories(minishell
        ${CMAKE_SOURCE_DIR}/include/
        ${CMAKE_SOURCE_DIR}/libft/include/)

target_link_libraries(minishell
        ${CMAKE_SOURCE_DIR}/libft/libft.a)