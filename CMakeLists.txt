cmake_minimum_required(VERSION 3.15)
project(second_project C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/wd5045)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
    link_libraries(msvcrt.lib legacy_stdio_definitions.lib)
endif()

include_directories(include src)

add_executable(hexdump
    src/main.c
    src/lib_main.c
    src/getopt.c
)