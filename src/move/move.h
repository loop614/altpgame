//
// Created by loop on 7/7/23.
//

#ifndef ALTPRO_MOVE_H
#define ALTPRO_MOVE_H

#include "../common/common.h"

void do_move(uint8* boardp, uint8* targetp, const uint8 targeth, const uint8 targetw, uint8* numberh, uint8* numberw, uint8* emptyh, uint8* emptyw);
void move_zero_to_number(uint8* boardp, const uint8 numberh, const uint8 numberw, uint8* emptyh, uint8* emptyw);

#endif //ALTPRO_MOVE_H
