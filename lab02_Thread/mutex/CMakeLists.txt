cmake_minimum_required(VERSION 3.13)
project(mutex C)

set(CMAKE_C_STANDARD 99)
find_package(Threads)
set(CMAKE_C_FLAGS -pthread)

add_executable(mutex main.c sync.c sync.h)