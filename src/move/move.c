//
// Created by loop on 7/7/23.
//

#include <stdbool.h>

#include "move.h"
#include "../operation/operation.h"

static void walk_zero_around(uint8 *boardp, uint8 *emptyh, uint8 *emptyw, enum_direction direction)
{
    if (direction == DIRECTION_UP) {
        if (*emptyw < BOARD_WIDTH - 1 && *emptyh - 1 > 0) {
            number_go_direction(boardp, emptyh, emptyw, DIRECTION_RIGHT);
            number_go_direction(boardp, emptyh, emptyw, DIRECTION_UP);
            number_go_direction(boardp, emptyh, emptyw, DIRECTION_UP);
            number_go_direction(boardp, emptyh, emptyw, DIRECTION_LEFT);
        } else {
            number_go_direction(boardp, emptyh, emptyw, DIRECTION_LEFT);
            number_go_direction(boardp, emptyh, emptyw, DIRECTION_UP);
            number_go_direction(boardp, emptyh, emptyw, DIRECTION_UP);
            number_go_direction(boardp, emptyh, emptyw, DIRECTION_RIGHT);
        }
    }
    if (direction == DIRECTION_LEFT) {
        if (*emptyh < BOARD_HEIGHT - 1 && *emptyw - 1 > 0) {
            number_go_direction(boardp, emptyh, emptyw, DIRECTION_DOWN);
            number_go_direction(boardp, emptyh, emptyw, DIRECTION_LEFT);
            number_go_direction(boardp, emptyh, emptyw, DIRECTION_LEFT);
            number_go_direction(boardp, emptyh, emptyw, DIRECTION_UP);
        } else {
            number_go_direction(boardp, emptyh, emptyw, DIRECTION_UP);
            number_go_direction(boardp, emptyh, emptyw, DIRECTION_LEFT);
            number_go_direction(boardp, emptyh, emptyw, DIRECTION_LEFT);
            number_go_direction(boardp, emptyh, emptyw, DIRECTION_DOWN);
        }
    }

    if (direction == DIRECTION_RIGHT) {
        if (*emptyh < BOARD_HEIGHT - 1 && *emptyw - 1 > 0) {
            number_go_direction(boardp, emptyh, emptyw, DIRECTION_DOWN);
            number_go_direction(boardp, emptyh, emptyw, DIRECTION_RIGHT);
            number_go_direction(boardp, emptyh, emptyw, DIRECTION_RIGHT);
            number_go_direction(boardp, emptyh, emptyw, DIRECTION_UP);
        } else {
            number_go_direction(boardp, emptyh, emptyw, DIRECTION_UP);
            number_go_direction(boardp, emptyh, emptyw, DIRECTION_RIGHT);
            number_go_direction(boardp, emptyh, emptyw, DIRECTION_RIGHT);
            number_go_direction(boardp, emptyh, emptyw, DIRECTION_DOWN);
        }
    }

    if (direction == DIRECTION_DOWN) {
        if (*emptyw < BOARD_WIDTH - 1 && *emptyh - 1 > 0) {
            number_go_direction(boardp, emptyh, emptyw, DIRECTION_RIGHT);
            number_go_direction(boardp, emptyh, emptyw, DIRECTION_DOWN);
            number_go_direction(boardp, emptyh, emptyw, DIRECTION_DOWN);
            number_go_direction(boardp, emptyh, emptyw, DIRECTION_LEFT);
        } else {
            number_go_direction(boardp, emptyh, emptyw, DIRECTION_LEFT);
            number_go_direction(boardp, emptyh, emptyw, DIRECTION_DOWN);
            number_go_direction(boardp, emptyh, emptyw, DIRECTION_DOWN);
            number_go_direction(boardp, emptyh, emptyw, DIRECTION_RIGHT);
        }
    }
}

void move_zero_to_number(uint8* boardp, const uint8 numberh, const uint8 numberw, uint8* emptyh, uint8* emptyw)
{
    while(numberh > *emptyh && !((numberh == (*emptyh) + 1) && numberw == *emptyw)) {
        number_go_direction(boardp, emptyh, emptyw, DIRECTION_DOWN);
    }

    while(numberh < *emptyh && !((numberh == (*emptyh) - 1) && numberw == *emptyw)) {
        number_go_direction(boardp, emptyh, emptyw, DIRECTION_UP);
    }

    while(numberw - 1 > *emptyw && !((numberh == *emptyh) && numberw == (*emptyw) + 1)) {
        number_go_direction(boardp, emptyh, emptyw, DIRECTION_RIGHT);
    }

    while(numberh < *emptyh && !((numberh == (*emptyh) - 1) && numberw == *emptyw)) {
        number_go_direction(boardp, emptyh, emptyw, DIRECTION_LEFT);
    }
}

void do_move(uint8* boardp, uint8* targetp, const uint8 targeth, const uint8 targetw, uint8* numberh, uint8* numberw, uint8* emptyh, uint8* emptyw) {
    bool zero_go_left = true;
    bool zero_go_up = true;
    bool zero_go_right = true;
    bool zero_go_down = true;
    bool condition_stop_left = false;
    bool condition_stop_up = false;
    bool condition_stop_right = false;
    bool condition_stop_down = false;
    bool zero_up_of_number = false;
    bool zero_down_of_number = false;
    bool zero_left_of_number = false;
    bool zero_right_of_number = false;
    bool target_left_of_zero = false;
    bool target_right_of_zero = false;
    bool target_up_of_zero = false;
    bool target_down_of_zero = false;

    while (true) {
        target_left_of_zero = targetw < *emptyw;
        target_right_of_zero = targetw > *emptyw;
        target_up_of_zero = targeth < *emptyh;
        target_down_of_zero = targeth > *emptyh;

        zero_down_of_number = (*numberh)+1 == *emptyh && *numberw == *emptyw;
        zero_left_of_number = (*numberh == *emptyh && *numberw == (*emptyw)+1);
        zero_right_of_number = (*numberh == *emptyh && *numberw == (*emptyw)-1);
        zero_up_of_number = (*numberh)-1 == *emptyh && *numberw == *emptyw;

        zero_go_left = target_left_of_zero && !zero_right_of_number && *emptyw != (*numberw)-1;
        zero_go_up = target_up_of_zero && !zero_down_of_number && *emptyh != (*numberh)-1;
        zero_go_right = target_right_of_zero && !zero_left_of_number && *emptyw != (*numberw)+1;
        zero_go_down = target_down_of_zero && !zero_up_of_number && *emptyh != (*numberh)+1;

        condition_stop_down = zero_up_of_number && targeth < *numberh && *emptyh == (*numberh)-1;
        condition_stop_right = zero_left_of_number && targetw < *numberw && *emptyw == (*numberw)-1;
        condition_stop_up = zero_down_of_number && targeth > *numberh && *emptyh == (*numberh)+1;
        condition_stop_left = zero_right_of_number && targetw > *numberw && *emptyw == (*numberw)+1;

        if (condition_stop_down) {
            // just up, so move zero down
            *numberh = (*numberh) - 1;
            number_go_direction(boardp, emptyh, emptyw, DIRECTION_DOWN);
            break;
        }
        if (condition_stop_right) {
            // just left, so move zero right
            *numberw = (*numberw) - 1;
            number_go_direction(boardp, emptyh, emptyw, DIRECTION_RIGHT);
            break;
        }
        if (condition_stop_up) {
            // just down, so move zero up
            *numberh = (*numberh) + 1;
            number_go_direction(boardp, emptyh, emptyw, DIRECTION_UP);
            break;
        }
        if (condition_stop_left) {
            // just right, so move zero left
            *numberw = (*numberw) + 1;
            number_go_direction(boardp, emptyh, emptyw, DIRECTION_LEFT);
            break;
        }

        if (*emptyw == targetw && zero_down_of_number) {
            walk_zero_around(boardp, emptyh, emptyw, DIRECTION_UP);
            continue;
        }

        if (*emptyh == targeth && zero_right_of_number) {
            walk_zero_around(boardp, emptyh, emptyw, DIRECTION_LEFT);
            continue;
        }

        if (*emptyh == targeth && zero_left_of_number) {
            walk_zero_around(boardp, emptyh, emptyw, DIRECTION_RIGHT);
            continue;
        }

        if (*emptyw == targetw && zero_up_of_number) {
            walk_zero_around(boardp, emptyh, emptyw, DIRECTION_DOWN);
            continue;
        }

        if (zero_go_left) {
            number_go_direction(boardp, emptyh, emptyw, DIRECTION_LEFT);
            continue;
        }
        if (zero_go_right) {
            number_go_direction(boardp, emptyh, emptyw, DIRECTION_RIGHT);
            continue;
        }
        if (zero_go_down) {
            number_go_direction(boardp, emptyh, emptyw, DIRECTION_DOWN);
            continue;
        }
        if (zero_go_up)  {
            number_go_direction(boardp, emptyh, emptyw, DIRECTION_UP);
            continue;
        }
    }
}
