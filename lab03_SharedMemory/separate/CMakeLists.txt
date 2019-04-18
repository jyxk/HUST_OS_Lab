cmake_minimum_required(VERSION 3.13)
project(separate C)

set(CMAKE_C_STANDARD 99)

add_executable(main main.c sem.c)
add_executable(reader reader.c sem.c )
add_executable(writer writer.c sem.c )