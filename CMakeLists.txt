cmake_minimum_required(VERSION 3.7)
set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES
        src/main.c
        src/get_env.c
        src/prompt_message.c
        src/freedom.c
        src/exec_commands.c
        src/utils.c
        src/my_setenv.c
        src/error.c
        src/my_cd.c
        src/my_unsetenv.c
        src/my_echo.c
        src/my_env.c
        src/signals.c
        )

add_executable(minishell ${SOURCE_FILES})

include_directories(minishell
        ${CMAKE_SOURCE_DIR}/include/
        ${CMAKE_SOURCE_DIR}/libft/include/)

target_link_libraries(minishell
        ${CMAKE_SOURCE_DIR}/libft/libft.a)