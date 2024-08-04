cmake_minimum_required(VERSION 3.28)
project(dratevka C)

set(CMAKE_C_STANDARD 17)

add_executable(dratevka main.c
        config/config.c
        config/config.h
        help/help.c
        help/help.h
)
