cmake_minimum_required(VERSION 3.13)
project(lab02_Thread C)

set(CMAKE_C_STANDARD 11)
find_package(Threads)
set(CMAKE_C_FLAGS -pthread)
include_directories(.)

add_executable(lab02_Thread
        sync.c
        sync.h
        main.c)
