//
// Created by loop on 7/3/23.
//

#ifndef ALTPRO_BOARD_H
#define ALTPRO_BOARD_H

#include <stdbool.h>
#include "common/common.h"

void allocateBoards(uint8 ***board, uint8 ***target_board);
void deallocateBoards(uint8 ***board, uint8 ***target_board);
void print_board(uint8 **cp);
void sort_board(uint8 **board, uint8 **target_board);

#endif //ALTPRO_BOARD_H
