cmake_minimum_required(VERSION 3.25)
project(altpro C)

set(CMAKE_C_STANDARD 11)

add_executable(
    altpro
    main.c
    src/board.c src/board.h
    src/common/common.h
    src/operation/operation.c src/operation/operation.h
    src/move/move.c src/move/move.h
)
