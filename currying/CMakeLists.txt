cmake_minimum_required(VERSION 3.22)
project(lock_free_stack)

set(CMAKE_CXX_STANDARD 20)

if (MSVC)
    add_compile_options(-W4)
endif (MSVC)

if (LINUX)
    add_compile_options(-Wall -Wpedantic -Wconversion -O3)
endif (LINUX)

add_executable(lock_free_stack test.cpp currying.h test.cpp)

target_include_directories(lock_free_stack PUBLIC ../common)
