//
// Created by loop on 7/3/23.
//

#ifndef ALTPRO_BOARD_H
#define ALTPRO_BOARD_H

#include <stdbool.h>

#define BOARD_WIDTH 4
#define BOARD_HEIGHT 4

typedef char unit8;

typedef enum {
    DIRECTION_UP,
    DIRECTION_DOWN,
    DIRECTION_LEFT,
    DIRECTION_RIGHT
} enum_direction;

void print_board(const unit8* cp);
bool is_board_ordered(const unit8* cp, const unit8* target);
void find_position(const unit8* cp, unit8* pos1h, unit8* pos1w, const unit8 needle);
void swap_numbers(unit8* boardp, unit8 pos1h, unit8 pos1w, unit8 pos2h, unit8 pos2w);
void number_go_direction(unit8* boardp, unit8* weighth, unit8* weightw, enum_direction direction);
void do_move(unit8* boardp, const unit8 targeth, const unit8 targetw, unit8* numberh, unit8* numberw, unit8* emptyh, unit8* emptyw);

#endif //ALTPRO_BOARD_H
