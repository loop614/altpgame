//
// Created by loop on 7/7/23.
//

#include <assert.h>
#include <stdbool.h>

#include "operation.h"

static void swap_numbers(uint8* boardp, Point pos1, Point pos2);

void find_position(const uint8* cp, Point* position, const uint8 needle)
{
    for (uint8 i = 0; i < BOARD_HEIGHT; i++) {
        for (uint8 j = 0; j < BOARD_WIDTH; j++) {
            if (*((cp+i*BOARD_WIDTH) + j) == needle) {
                position->height = i;
                position->width = j;

                return;
            }
        }
    }
}

void number_go_direction(uint8* boardp, Point* weight, EnumDirection direction)
{
    Point temp;
    switch (direction) {
        case DIRECTION_UP:
            assert(weight->height - 1 >= 0);
            temp.height = weight->height - 1;
            temp.width = weight->width;
            swap_numbers(boardp, *weight, temp);
            weight->height--;
            break;
        case DIRECTION_DOWN:
            assert(weight->height + 1 <= BOARD_HEIGHT);
            temp.height = weight->height + 1;
            temp.width = weight->width;
            swap_numbers(boardp, *weight, temp);
            weight->height++;
            break;
        case DIRECTION_RIGHT:
            assert(weight->width + 1 <= BOARD_WIDTH);
            temp.height = weight->height;
            temp.width = weight->width + 1;
            swap_numbers(boardp, temp, *weight);
            weight->width++;
            break;
        case DIRECTION_LEFT:
            assert(weight->width - 1 >= 0);
            temp.height = weight->height;
            temp.width = weight->width - 1;
            swap_numbers(boardp, temp, *weight);
            weight->width--;
            break;
        default:
            assert(false);
    }
}

static void swap_numbers(uint8* boardp, Point pos1, Point pos2)
{
    assert(*((boardp+pos1.height*BOARD_WIDTH) + pos1.width) == 0 || *((boardp+pos2.height*BOARD_WIDTH) + pos2.width) == 0 );

    uint8 temp = *((boardp+pos1.height*BOARD_WIDTH) + pos1.width);
    *((boardp+pos1.height*BOARD_WIDTH) + pos1.width) = *((boardp+pos2.height*BOARD_WIDTH) + pos2.width);
    *((boardp+pos2.height*BOARD_WIDTH) + pos2.width) = temp;
}
