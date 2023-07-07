//
// Created by loop on 7/3/23.
//

#include <stdio.h>
#include <stdlib.h>

#include "board.h"
#include "operation/operation.h"
#include "move/move.h"

static void do_one_two_three(uint8 **board, uint8 **target_board);
static void do_four(uint8 **board, uint8 **target_board);
static void do_second_row(uint8 **board, uint8 **target_board);
static void do_third_row(uint8 **board, uint8 **target_board);
static void do_fourth_row(uint8 **board, uint8 **target_board);

void sort_board(uint8 **board, uint8 **target_board) {
    do_one_two_three(board, target_board);
    do_four(board, target_board);
    do_second_row(board, target_board);
    do_third_row(board, target_board);
    do_fourth_row(board, target_board);
}

void print_board(uint8 **board) {
    for (uint8 i = 0; i < BOARD_HEIGHT; i++) {
        for (uint8 j = 0; j < BOARD_WIDTH; j++) {
            printf("%d\t ", board[i][j]);
        }
        printf("\n");
    }
    printf("---------------------------\n");
}

void allocateBoards(uint8 ***board, uint8 ***target_board) {
    (*board) = (uint8**) malloc(BOARD_WIDTH * sizeof (uint8*));
    (*target_board) = (uint8**) malloc(BOARD_WIDTH * sizeof (uint8*));
    for (int i = 0; i < BOARD_WIDTH; i++) {
        (*board)[i] = (uint8*) malloc(BOARD_HEIGHT * sizeof (uint8));
        (*target_board)[i] = (uint8*) malloc(BOARD_HEIGHT * sizeof (uint8));
    }

    for(int i = 0; i < BOARD_HEIGHT; i++) {
        for(int j = 0; j < BOARD_WIDTH; j++) {
            (*board)[i][j] = (BOARD_HEIGHT * BOARD_WIDTH - 1) - (i * BOARD_HEIGHT + j);
            (*target_board)[i][j] = i * BOARD_HEIGHT + j + 1;
        }
    }
    (*target_board)[BOARD_HEIGHT - 1][BOARD_WIDTH - 1] = 0;
}

void deallocateBoards(uint8 ***board, uint8 ***target_board) {
    for (int i = 0; i < BOARD_WIDTH; i++) {
        free ((*board)[i]);
        free ((*target_board)[i]);
    }
    free (*board);
    free (*target_board);
}

static void do_one_two_three(uint8 **board, uint8 **target_board) {
    Point zero;
    find_position(board, &zero, 0);
    print_board(board);
    for (uint8 i = 1; i < BOARD_HEIGHT  *BOARD_WIDTH; ++i) {
        Point number, target;
        find_position(target_board, &target, i);
        find_position(board, &number, i);
        while (number.height != target.height || number.width != target.width) {
            move_zero_to_number(board, number,  &zero);
            do_move(board, target_board, &target, &number, &zero);
            print_board(board);
        }

        if (i > 1) {
            break;
        }
    }
}

static void do_four(uint8 **board, uint8 **target_board) {
}

static void do_second_row(uint8 **board, uint8 **target_board) {
}

static void do_third_row(uint8 **board, uint8 **target_board) {
}

static void do_fourth_row(uint8 **board, uint8 **target_board) {
}
