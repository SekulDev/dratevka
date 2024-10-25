cmake_minimum_required(VERSION 3.28)
project(dratevka C)

set(CMAKE_C_STANDARD 17)

include_directories(include)
add_executable(dratevka main.c
        src/config.c
        src/help.c
        src/prompt.c
)

if(WIN32)
    target_compile_definitions(dratevka PRIVATE _WIN32)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(dratevka PRIVATE _IS_DEBUG)
    message(STATUS "Debug mode: IS_DEBUG defined")
endif ()