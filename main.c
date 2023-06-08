#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#define BOARD_WIDTH 4
#define BOARD_HEIGHT 4

typedef enum {
    DIRECTION_UP,
    DIRECTION_DOWN,
    DIRECTION_LEFT,
    DIRECTION_RIGHT
} enum_direction;

void print_empty_line() {
    printf("\n--------------------\n");
}

void print_board(const char* cp) {
    for (char i = 0; i < BOARD_HEIGHT; i++) {
        for (char j = 0; j < BOARD_WIDTH; j++) {
            printf("%x\t ", *((cp+i*BOARD_WIDTH) + j));
        }
        printf("\n");
    }
    printf("---------------------------\n");
}

bool is_board_ordered(const char* cp) {
    char temp = 0;
    for (char i = 0; i < BOARD_HEIGHT; i++) {
        for (char j = 0; j < BOARD_WIDTH; j++) {
            if (temp != *((cp+i*BOARD_WIDTH) + j)) {
                return false;
            }
            temp = *((cp+i*BOARD_WIDTH) + j);
        }
    }
    return true;
}

void find_position(const char* cp, char* pos1h, char* pos1w, const char needle) {
    for (char i = 0; i < BOARD_HEIGHT; i++) {
        for (char j = 0; j < BOARD_WIDTH; j++) {
            if (*((cp+i*BOARD_WIDTH) + j) == needle) {
                *pos1h = i;
                *pos1w = j;

                return;
            }
        }
    }
}

void swap_numbers(char* boardp, char pos1h, char pos1w, char pos2h, char pos2w) {
    assert(*((boardp+pos1h*BOARD_WIDTH) + pos1w) == 0 || *((boardp+pos2h*BOARD_WIDTH) + pos2w) == 0 );

    char temp = *((boardp+pos1h*BOARD_WIDTH) + pos1w);
    *((boardp+pos1h*BOARD_WIDTH) + pos1w) = *((boardp+pos2h*BOARD_WIDTH) + pos2w);
    *((boardp+pos2h*BOARD_WIDTH) + pos2w) = temp;
}

void number_go_direction(char* boardp, char* weighth, char* weightw, enum_direction direction) {
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

void do_one_move(char* boardp, const char targeth, const char targetw, char* numberh, char* numberw, char* emptyh, char* emptyw) {
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

int main() {
    char board[BOARD_HEIGHT][BOARD_WIDTH] = {
        {15, 14, 13, 12},
        {11, 10, 9, 8},
        {7, 6, 5, 4},
        {3, 2, 1, 0},
    };

    char target_board[BOARD_HEIGHT][BOARD_WIDTH] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 0},
    };

    char *boardp = &(board[0][0]);
    char *targetp = &(target_board[0][0]);
    char emptyh, emptyw;
    find_position(boardp, &emptyh, &emptyw, 0);

    print_board(boardp);
    for (char i = 1; i < BOARD_HEIGHT * BOARD_WIDTH; i++) {
        char numberh, numberw;
        char targeth, targetw;
        find_position(targetp, &targeth, &targetw, i);
        find_position(boardp, &numberh, &numberw, i);
        char counter = 0;

        while (numberh != targeth || numberw != targetw) {
            do_one_move(boardp, targeth, targetw, &numberh, &numberw, &emptyh, &emptyw);
            counter++;
            if (counter > 15) {
                break;
            }
        }

        break;
    }

    return 0;
}
