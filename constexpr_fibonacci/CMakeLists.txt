cmake_minimum_required(VERSION 3.22)
project(constexpr_fibonacci)

set(CMAKE_CXX_STANDARD 20)

if (MSVC)
    add_compile_options(-W4)
endif (MSVC)

if (LINUX)
    add_compile_options(-Wall -Wpedantic -Wconversion -O3)
endif (LINUX)

add_executable(constexpr_fibonacci main.cpp)

target_include_directories(constexpr_fibonacci PUBLIC ../common)