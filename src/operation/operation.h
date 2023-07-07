//
// Created by loop on 7/7/23.
//

#ifndef ALTPRO_OPERATION_H
#define ALTPRO_OPERATION_H

#include "../common/common.h"

void number_go_direction(uint8* boardp, uint8* weighth, uint8* weightw, enum_direction direction);
void swap_numbers(uint8* boardp, uint8 pos1h, uint8 pos1w, uint8 pos2h, uint8 pos2w);
void find_position(const uint8* cp, uint8* pos1h, uint8* pos1w, const uint8 needle);

#endif //ALTPRO_OPERATION_H
