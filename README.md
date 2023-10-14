## Description
- [15 puzzle](https://en.wikipedia.org/wiki/15_puzzle)
- using 2D arrays
- only moves with 0 allowed

## Requirements
- cmake, ninja, build-essentials

## Status
- numbers 1 and 2 work
- for number 3 check for numbers already in place
- make 'snake' pattern players use to play game

## Quick Start
```console
$ mkdir cmake-build-debug
$ cmake -B cmake-build-debug/ -G Ninja .
$ ninja -C cmake-build-debug/
$ ./altpro
```

### Board:
- 15   14   13   12
- 11   10    9    8
- 7     6    5    4
- 3     2    1    0

### Target board:
- 0     1    2    3
- 4     5    6    7
- 8     9   10   11
- 12   13   14   15
