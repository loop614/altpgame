//
// Created by loop on 7/7/23.
//

#include <assert.h>
#include <stdbool.h>

#include "operation.h"

void find_position(uint8 **board, Point *position, const uint8 needle) {
    for (uint8 i = 0; i < BOARD_HEIGHT; i++) {
        for (uint8 j = 0; j < BOARD_WIDTH; j++) {
            if (board[i][j] == needle) {
                position->height = i;
                position->width = j;

                return;
            }
        }
    }
}

void number_go_direction(uint8 **board, Point *point, EnumDirection direction) {
    uint8 temp;
    switch (direction) {
        case DIRECTION_UP:
            assert(point->height > 0);
            assert(board[point->height][point->width] == 0 || board[point->height-1][point->width] == 0 );
            temp = board[point->height][point->width];
            board[point->height][point->width] = board[point->height-1][point->width];
            board[point->height-1][point->width] = temp;
            point->height--;
            break;
        case DIRECTION_DOWN:
            assert(point->height < BOARD_HEIGHT);
            assert(board[point->height][point->width] == 0 || board[point->height+1][point->width] == 0 );
            temp = board[point->height][point->width];
            board[point->height][point->width] = board[point->height+1][point->width];
            board[point->height+1][point->width] = temp;
            point->height++;
            break;
        case DIRECTION_RIGHT:
            assert(point->width < BOARD_WIDTH);
            assert(board[point->height][point->width+1] == 0 || board[point->height][point->width] == 0 );
            temp = board[point->height][point->width+1];
            board[point->height][point->width+1] = board[point->height][point->width];
            board[point->height][point->width] = temp;
            point->width++;
            break;
        case DIRECTION_LEFT:
            assert(point->width > 0);
            assert(board[point->height][point->width-1] == 0 || board[point->height][point->width] == 0 );
            temp = board[point->height][point->width-1];
            board[point->height][point->width-1] = board[point->height][point->width];
            board[point->height][point->width] = temp;
            point->width--;
            break;
        default:
            assert(false);
    }
}
