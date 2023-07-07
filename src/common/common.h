//
// Created by loop on 7/7/23.
//

#ifndef ALTPRO_COMMON_H
#define ALTPRO_COMMON_H

#define BOARD_WIDTH 4
#define BOARD_HEIGHT 4

typedef char uint8;

typedef enum {
    DIRECTION_UP,
    DIRECTION_DOWN,
    DIRECTION_LEFT,
    DIRECTION_RIGHT
} EnumDirection;

typedef struct {
    uint8 width;
    uint8 height;
    bool is_at_target;
} Point;

#endif //ALTPRO_COMMON_H
