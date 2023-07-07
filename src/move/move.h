//
// Created by loop on 7/7/23.
//

#ifndef ALTPRO_MOVE_H
#define ALTPRO_MOVE_H

#include "../common/common.h"

void do_move(uint8 **board, uint8 **target_board, const Point *target, Point *number, Point *zero);
void move_zero_to_number(uint8 **board, const Point number, Point *zero);

#endif //ALTPRO_MOVE_H
