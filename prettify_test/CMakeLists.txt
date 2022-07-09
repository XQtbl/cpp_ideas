cmake_minimum_required(VERSION 3.22)
project(prettify_test)

set(CMAKE_CXX_STANDARD 20)

if (MSVC)
    add_compile_options(-W4)
endif (MSVC)

if (LINUX)
    add_compile_options(-Wall -Wpedantic -Wconversion -O3)
endif (LINUX)

add_executable(prettify_test test.cpp)

target_include_directories(prettify_test PUBLIC ../common)
