cmake_minimum_required(VERSION 3.28)
project(dratevka C)

set(CMAKE_C_STANDARD 17)

target_include_directories(src/include)
add_executable(dratevka main.c
        src/config.c
        src/help.c
        include/config.h
        include/help.h
)
