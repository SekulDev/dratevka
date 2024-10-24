cmake_minimum_required(VERSION 3.28)
project(dratevka C)

set(CMAKE_C_STANDARD 17)

include_directories(src/include)
add_executable(dratevka main.c
        src/config.c
        src/help.c
        src/include/config.h
        src/include/help.h
        src/include/prompt.h
        src/prompt.c
)

if(WIN32)
    target_compile_definitions(dratevka PRIVATE _WIN32)
endif()
