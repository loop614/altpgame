//
// Created by loop on 7/3/23.
//

#include <stdio.h>
#include <assert.h>

#include "board.h"

void print_board(const unit8* cp) {
    for (unit8 i = 0; i < BOARD_HEIGHT; i++) {
        for (unit8 j = 0; j < BOARD_WIDTH; j++) {
            printf("%x\t ", *((cp+i*BOARD_WIDTH) + j));
        }
        printf("\n");
    }
    printf("---------------------------\n");
}

bool is_board_ordered(const unit8* cp, const unit8* target) {
    for (unit8 i = 0; i < BOARD_HEIGHT; i++) {
        for (unit8 j = 0; j < BOARD_WIDTH; j++) {
            if (*((target+i*BOARD_WIDTH) + j) != *((cp+i*BOARD_WIDTH) + j)) {
                return false;
            }
        }
    }
    return true;
}

void find_position(const unit8* cp, unit8* pos1h, unit8* pos1w, const unit8 needle) {
    for (unit8 i = 0; i < BOARD_HEIGHT; i++) {
        for (unit8 j = 0; j < BOARD_WIDTH; j++) {
            if (*((cp+i*BOARD_WIDTH) + j) == needle) {
                *pos1h = i;
                *pos1w = j;

                return;
            }
        }
    }
}

void swap_numbers(unit8* boardp, unit8 pos1h, unit8 pos1w, unit8 pos2h, unit8 pos2w) {
    assert(*((boardp+pos1h*BOARD_WIDTH) + pos1w) == 0 || *((boardp+pos2h*BOARD_WIDTH) + pos2w) == 0 );

    unit8 temp = *((boardp+pos1h*BOARD_WIDTH) + pos1w);
    *((boardp+pos1h*BOARD_WIDTH) + pos1w) = *((boardp+pos2h*BOARD_WIDTH) + pos2w);
    *((boardp+pos2h*BOARD_WIDTH) + pos2w) = temp;
}

void number_go_direction(unit8* boardp, unit8* weighth, unit8* weightw, enum_direction direction) {
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
    print_board(boardp);
}

void do_move(unit8* boardp, const unit8 targeth, const unit8 targetw, unit8* numberh, unit8* numberw, unit8* emptyh, unit8* emptyw) {
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

        zero_up_of_number = (*numberh)+1 == *emptyh && *numberw == *emptyw;
        zero_left_of_number = (*numberh == *emptyh && *numberw == (*emptyw)+1);
        zero_right_of_number = (*numberh == *emptyh && *numberw == (*emptyw)-1);
        zero_down_of_number = (*numberh)-1 == *emptyh && *numberw == *emptyw;

        zero_go_left = target_left_of_zero && !zero_right_of_number && *emptyw != (*numberw)-1;
        zero_go_up = target_up_of_zero && !zero_down_of_number && *emptyh != (*numberh)-1;
        zero_go_right = target_right_of_zero && !zero_left_of_number && *emptyw != (*numberw)+1;
        zero_go_down = target_down_of_zero && !zero_up_of_number && *emptyh != (*numberh)+1;

        condition_stop_down = zero_down_of_number && targeth < *numberh && *emptyh == (*numberh)-1;
        condition_stop_right = zero_left_of_number && targetw < *numberw && *emptyw == (*numberw)-1;
        condition_stop_up = zero_up_of_number && targeth > *numberh && *emptyh == (*numberh)+1;
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
