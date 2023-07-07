//
// Created by loop on 7/3/23.
//

#include <stdio.h>

#include "board.h"
#include "operation/operation.h"
#include "move/move.h"

static void do_one_two_three(uint8* boardp, uint8* targetp)
{
    uint8 emptyh, emptyw;
    find_position(boardp, &emptyh, &emptyw, 0);
    print_board(boardp);
    for (uint8 i = 1; i < BOARD_HEIGHT * BOARD_WIDTH; ++i) {
        uint8 numberh, numberw;
        uint8 targeth, targetw;
        find_position(targetp, &targeth, &targetw, i);
        find_position(boardp, &numberh, &numberw, i);
        while (numberh != targeth || numberw != targetw) {
            move_zero_to_number(boardp, numberh, numberw, &emptyh, &emptyw);
            do_move(boardp, targetp, targeth, targetw, &numberh, &numberw, &emptyh, &emptyw);
            print_board(boardp);
        }

        if (i > 1) {
            break;
        }
    }
}

static void do_four(uint8* boardp, uint8* targetp)
{
}

static void do_second_row(uint8* boardp, uint8* targetp)
{
}

static void do_third_row(uint8* boardp, uint8* targetp)
{
}

static void do_fourth_row(uint8* boardp, uint8* targetp)
{
}

void sort_board(uint8* boardp, uint8* targetp)
{
    do_one_two_three(boardp, targetp);
    do_four(boardp, targetp);
    do_second_row(boardp, targetp);
    do_third_row(boardp, targetp);
    do_fourth_row(boardp, targetp);
}

void print_board(const uint8* cp) {
    for (uint8 i = 0; i < BOARD_HEIGHT; i++) {
        for (uint8 j = 0; j < BOARD_WIDTH; j++) {
            printf("%d\t ", *((cp+i*BOARD_WIDTH) + j));
        }
        printf("\n");
    }
    printf("---------------------------\n");
}
