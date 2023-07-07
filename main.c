#include "src/board.h"

int main() {
    uint8** board;
    uint8** target_board;
    allocateBoards(&board, &target_board);

//    ---------------------------
//    board:
//    ---------------------------
//    15       14      13      12
//    11       10      9       8
//    7        6       5       4
//    3        2       1       0
//    ---------------------------
//    target_board:
//    ---------------------------
//    0        1       2       3
//    4        5       6       7
//    8        9       10      11
//    12       13      14      15

    sort_board(board, target_board);
    // print_board(board);

    deallocateBoards(&board, &target_board);
    return 0;
}
