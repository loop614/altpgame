#include "src/board.h"

int main() {
    uint8 board[BOARD_HEIGHT][BOARD_WIDTH] = {
        {15, 14, 13, 12},
        {11, 10, 9, 8},
        {7, 6, 5, 4},
        {3, 2, 1, 0},
    };

    uint8 target_board[BOARD_HEIGHT][BOARD_WIDTH] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 0},
    };

    sort_board(&(board[0][0]), &(target_board[0][0]));
    // print_board(&(board[0][0]));

    return 0;
}
