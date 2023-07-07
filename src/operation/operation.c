//
// Created by loop on 7/7/23.
//

#include <assert.h>
#include <stdbool.h>

#include "operation.h"

void number_go_direction(uint8* boardp, uint8* weighth, uint8* weightw, enum_direction direction) {
    switch (direction) {
        case DIRECTION_UP:
            assert((*weighth) - 1 >= 0);
            swap_numbers(boardp, *weighth, *weightw, (*weighth) - 1, *weightw);
            *weighth = (*weighth) - 1;
            break;
        case DIRECTION_DOWN:
            assert((*weighth) + 1 <= BOARD_HEIGHT);
            swap_numbers(boardp, *weighth, *weightw, (*weighth) + 1, *weightw);
            *weighth = (*weighth) + 1;
            break;
        case DIRECTION_RIGHT:
            assert((*weightw) + 1 <= BOARD_WIDTH);
            swap_numbers(boardp, *weighth, (*weightw) + 1, *weighth, *weightw);
            *weightw = (*weightw) + 1;
            break;
        case DIRECTION_LEFT:
            assert((*weightw) - 1 >= 0);
            swap_numbers(boardp, *weighth, (*weightw) - 1, *weighth, *weightw);
            *weightw = (*weightw) - 1;
            break;
        default:
            assert(false);
    }
}

void swap_numbers(uint8* boardp, uint8 pos1h, uint8 pos1w, uint8 pos2h, uint8 pos2w) {
    assert(*((boardp+pos1h*BOARD_WIDTH) + pos1w) == 0 || *((boardp+pos2h*BOARD_WIDTH) + pos2w) == 0 );

    uint8 temp = *((boardp+pos1h*BOARD_WIDTH) + pos1w);
    *((boardp+pos1h*BOARD_WIDTH) + pos1w) = *((boardp+pos2h*BOARD_WIDTH) + pos2w);
    *((boardp+pos2h*BOARD_WIDTH) + pos2w) = temp;
}

void find_position(const uint8* cp, uint8* pos1h, uint8* pos1w, const uint8 needle) {
    for (uint8 i = 0; i < BOARD_HEIGHT; i++) {
        for (uint8 j = 0; j < BOARD_WIDTH; j++) {
            if (*((cp+i*BOARD_WIDTH) + j) == needle) {
                *pos1h = i;
                *pos1w = j;

                return;
            }
        }
    }
}
