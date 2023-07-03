#include "src/board.h"

int main() {
    unit8 board[BOARD_HEIGHT][BOARD_WIDTH] = {
        {15, 14, 13, 12},
        {11, 10, 9, 8},
        {7, 6, 5, 4},
        {3, 2, 1, 0},
    };

    unit8 target_board[BOARD_HEIGHT][BOARD_WIDTH] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 0},
    };

    unit8 *boardp = &(board[0][0]);
    unit8 *targetp = &(target_board[0][0]);
    unit8 emptyh, emptyw;
    find_position(boardp, &emptyh, &emptyw, 0);

    print_board(boardp);
    for (unit8 i = 1; i < BOARD_HEIGHT * BOARD_WIDTH; i++) {
        unit8 numberh, numberw;
        unit8 targeth, targetw;
        find_position(targetp, &targeth, &targetw, i);
        find_position(boardp, &numberh, &numberw, i);
        unit8 counter = 0;

        while (numberh != targeth || numberw != targetw) {
            do_move(boardp, targeth, targetw, &numberh, &numberw, &emptyh, &emptyw);
            counter++;
            if (counter > 15) {
                break;
            }
        }

        break;
    }

    return 0;
}
