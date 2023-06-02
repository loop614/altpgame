#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#define BOARD_WIDTH 4
#define BOARD_HEIGHT 4

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

void swap_numbers(char* boardp, char pos1h, char pos1w, char pos2h, char pos2w) {
    assert(*((boardp+pos1h*BOARD_WIDTH) + pos1w) == 0 || *((boardp+pos2h*BOARD_WIDTH) + pos2w) == 0 );

    char temp = *((boardp+pos1h*BOARD_WIDTH) + pos1w);
    *((boardp+pos1h*BOARD_WIDTH) + pos1w) = *((boardp+pos2h*BOARD_WIDTH) + pos2w);
    *((boardp+pos2h*BOARD_WIDTH) + pos2w) = temp;
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

void number_go_up(char* boardp, char weight) {
    char emptyh, emptyw;
    find_position(boardp, &emptyh, &emptyw, weight);
    assert(emptyh - 1 >= 0);
    swap_numbers(boardp, emptyh, emptyw, emptyh - 1, emptyw);
}

void number_go_left(char* boardp, char weight) {
    char emptyh, emptyw;
    find_position(boardp, &emptyh, &emptyw, weight);
    assert(emptyw - 1 >= 0);
    swap_numbers(boardp, emptyh, emptyw, emptyh, emptyw - 1);
}

void number_go_down(char* boardp, char weight) {
    char emptyh, emptyw;
    find_position(boardp, &emptyh, &emptyw, weight);
    assert(emptyh + 1 <= BOARD_HEIGHT);
    swap_numbers(boardp, emptyh, emptyw, emptyh + 1, emptyw);
}

void number_go_right(char* boardp, char weight) {
    char emptyh, emptyw;
    find_position(boardp, &emptyh, &emptyw, weight);
    assert(emptyw + 1 <= BOARD_WIDTH);
    swap_numbers(boardp, emptyh, emptyw, emptyh, emptyw + 1);
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

    print_board(boardp);

    for (char i = 1; i < BOARD_HEIGHT * BOARD_WIDTH; i++) {
        char numberh, numberw;
        char targeth, targetw;
        find_position(targetp, &targeth, &targetw, i);
        find_position(boardp, &numberh, &numberw, i);

        number_go_up(boardp, 0);
        number_go_left(boardp, 0);
        number_go_up(boardp, 1);

        number_go_left(boardp, 0);
        number_go_up(boardp, 0);
        number_go_up(boardp, 0);
        number_go_right(boardp, 0);
        number_go_up(boardp, 1);

        number_go_left(boardp, 0);
        number_go_up(boardp, 0);
        number_go_up(boardp, 0);
        number_go_right(boardp, 0);
        number_go_up(boardp, 1);

        number_go_left(boardp, 0);
        number_go_up(boardp, 0);
        number_go_left(boardp, 1);

        number_go_down(boardp, 0);
        number_go_left(boardp, 0);
        number_go_left(boardp, 0);
        number_go_up(boardp, 0);
        number_go_left(boardp, 1);

        print_board(boardp);

        break;
    }

    return 0;
}
