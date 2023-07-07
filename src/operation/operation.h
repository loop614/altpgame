//
// Created by loop on 7/7/23.
//

#ifndef ALTPRO_OPERATION_H
#define ALTPRO_OPERATION_H

#include "../common/common.h"

void number_go_direction(uint8* boardp, Point* weight, EnumDirection direction);
void find_position(const uint8* cp, Point* position, const uint8 needle);

#endif //ALTPRO_OPERATION_H
