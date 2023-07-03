cmake_minimum_required(VERSION 3.25)
project(altpro C)

set(CMAKE_C_STANDARD 11)

add_executable(altpro main.c main.h src/board.c src/board.h)
