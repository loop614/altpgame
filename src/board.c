//
// Created by loop on 7/3/23.
//

#include <stdio.h>

#include "board.h"
#include "operation/operation.h"
#include "move/move.h"

static void do_one_two_three(uint8* boardp, uint8* targetp)
{
    Point zero;
    find_position(boardp, &zero, 0);
    print_board(boardp);
    for (uint8 i = 1; i < BOARD_HEIGHT * BOARD_WIDTH; ++i) {
        Point number, target;
        find_position(targetp, &target, i);
        find_position(boardp, &number, i);
        while (number.height != target.height || number.width != target.width) {
            move_zero_to_number(boardp, number,  &zero);
            do_move(boardp, targetp, &target, &number, &zero);
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
