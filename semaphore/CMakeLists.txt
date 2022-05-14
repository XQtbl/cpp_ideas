cmake_minimum_required(VERSION 3.22)
project(semaphore)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(-Wall -Wpedantic -Wconversion -O3)

add_executable(semaphore test.cpp)

target_include_directories(semaphore PUBLIC ../common)

target_link_libraries(semaphore pthread)
