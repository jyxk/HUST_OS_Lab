cmake_minimum_required(VERSION 3.13)
project(lab03_SharedMemory C)

set(CMAKE_C_STANDARD 99)

add_executable(cp sem.c main.c)