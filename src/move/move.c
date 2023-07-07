//
// Created by loop on 7/7/23.
//

#include <stdbool.h>

#include "move.h"
#include "../operation/operation.h"

typedef struct {
    bool target_left;
    bool target_right;
    bool target_up;
    bool target_down;
} TargetZeroPosition;

typedef struct {
    bool zero_up;
    bool zero_down;
    bool zero_left;
    bool zero_right;
} ZeroNumberPosition;

typedef struct {
    bool up;
    bool right;
    bool down;
    bool left;
} ZeroGo;

typedef struct {
    bool up;
    bool right;
    bool down;
    bool left;
} ConditionStop;

static void hydrate_target_zero_position(const Point *target, const Point *zero, TargetZeroPosition *targetZeroPosition);
static void hydrate_zero_number_position(const Point *number, const Point *zero, ZeroNumberPosition *zeroNumberPosition);
static void hydrate_zero_go(const Point *number, const Point *zero, ZeroNumberPosition zeroNumberPosition, TargetZeroPosition targetZeroPosition, ZeroGo *zeroGo);
static void hydrate_condition_stop(const Point *target, const Point *number, const Point *zero, ZeroNumberPosition zeroNumberPosition, ConditionStop *conditionStop);
static void do_walk_zero_around(uint8 **board, Point *zero, EnumDirection direction);
static bool move_zero(uint8 **board, Point *zero, ZeroGo *zeroGo);
static bool walk_zero_around(uint8 **board, const Point *target, Point *zero, ZeroNumberPosition *zeroNumberPosition);
static bool check_break_condition(uint8 **board, Point *number, Point *zero, ConditionStop *conditionStop);

void move_zero_to_number(uint8 **board, const Point number, Point *zero) {
    while(number.height > zero->height && !((number.height == zero->height + 1) && number.width == zero->width)) {
        number_go_direction(board, zero, DIRECTION_DOWN);
    }

    while(number.height < zero->height && !((number.height == zero->height - 1) && number.width == zero->width)) {
        number_go_direction(board, zero, DIRECTION_UP);
    }

    while(number.width - 1 > zero->width && !((number.height == zero->height) && number.width == zero->width + 1)) {
        number_go_direction(board, zero, DIRECTION_RIGHT);
    }

    while(number.height < zero->height && !((number.height == zero->height - 1) && number.width == zero->width)) {
        number_go_direction(board, zero, DIRECTION_LEFT);
    }
}

void do_move(uint8 **board, uint8 **target_board, const Point *target, Point *number, Point *zero) {
    ZeroNumberPosition zeroNumberPosition = {0};
    TargetZeroPosition targetZeroPosition = {0};
    ZeroGo zeroGo = {0};
    ConditionStop conditionStop = {0};

    while (true) {
        hydrate_target_zero_position(target, zero, &targetZeroPosition);
        hydrate_zero_number_position(number, zero, &zeroNumberPosition);
        hydrate_zero_go(number, zero, zeroNumberPosition, targetZeroPosition, &zeroGo);
        hydrate_condition_stop(target, number, zero, zeroNumberPosition, &conditionStop);

        if (check_break_condition(board, number, zero, &conditionStop)) {
            break;
        }
        if (walk_zero_around(board, target, zero, &zeroNumberPosition)) {
            continue;
        }
        (void) move_zero(board, zero, &zeroGo);
    }
}

static bool check_break_condition(uint8 **board, Point *number, Point *zero, ConditionStop *conditionStop) {
    if ((*conditionStop).down) {
        // just up, so move zero down
        number->height--;
        number_go_direction(board, zero, DIRECTION_DOWN);
        return true;
    }
    if ((*conditionStop).right) {
        // just left, so move zero right
        number->width--;
        number_go_direction(board, zero, DIRECTION_RIGHT);
        return true;
    }
    if ((*conditionStop).up) {
        // just down, so move zero up
        number->height++;
        number_go_direction(board, zero, DIRECTION_UP);
        return true;
    }
    if ((*conditionStop).left) {
        // just right, so move zero left
        number->width++;
        number_go_direction(board, zero, DIRECTION_LEFT);
        return true;
    }
    return false;
}

static bool walk_zero_around(uint8 **board, const Point *target, Point *zero, ZeroNumberPosition *zeroNumberPosition) {
    if (zero->width == target->width && (*zeroNumberPosition).zero_down) {
        do_walk_zero_around(board, zero, DIRECTION_UP);
        return true;
    }

    if (zero->height == target->height && (*zeroNumberPosition).zero_right) {
        do_walk_zero_around(board, zero, DIRECTION_LEFT);
        return true;
    }

    if (zero->height == target->height && (*zeroNumberPosition).zero_left) {
        do_walk_zero_around(board, zero, DIRECTION_RIGHT);
        return true;
    }

    if (zero->width == target->width && (*zeroNumberPosition).zero_up) {
        do_walk_zero_around(board, zero, DIRECTION_DOWN);
        return true;
    }
    return false;
}

static bool move_zero(uint8 **board, Point *zero, ZeroGo *zeroGo) {
    if ((*zeroGo).left) {
        number_go_direction(board, zero, DIRECTION_LEFT);
        return true;
    }
    if ((*zeroGo).right) {
        number_go_direction(board, zero, DIRECTION_RIGHT);
        return true;
    }
    if ((*zeroGo).down) {
        number_go_direction(board, zero, DIRECTION_DOWN);
        return true;
    }
    if ((*zeroGo).up)  {
        number_go_direction(board, zero, DIRECTION_UP);
        return true;
    }
    return false;
}

static void hydrate_condition_stop(const Point *target, const Point *number, const Point *zero, ZeroNumberPosition zeroNumberPosition, ConditionStop *conditionStop) {
    (*conditionStop).down = zeroNumberPosition.zero_up && target->height < number->height && zero->height == number->height - 1;
    (*conditionStop).right = zeroNumberPosition.zero_left && target->width < number->width && zero->width == number->width - 1;
    (*conditionStop).up = zeroNumberPosition.zero_down && target->height > number->height && zero->height == number->height + 1;
    (*conditionStop).left = zeroNumberPosition.zero_right && target->width > number->width && zero->width == number->width + 1;
}

static void hydrate_zero_go(const Point *number, const Point *zero, ZeroNumberPosition zeroNumberPosition, TargetZeroPosition targetZeroPosition, ZeroGo *zeroGo) {
    (*zeroGo).left = targetZeroPosition.target_left && !zeroNumberPosition.zero_right && zero->width != number->width - 1;
    (*zeroGo).up = targetZeroPosition.target_up && !zeroNumberPosition.zero_down && zero->height != number->height - 1;
    (*zeroGo).right = targetZeroPosition.target_right && !zeroNumberPosition.zero_left && zero->width != number->width + 1;
    (*zeroGo).down = targetZeroPosition.target_down && !zeroNumberPosition.zero_up && zero->height != number->height + 1;
}

static void hydrate_zero_number_position(const Point *number, const Point *zero, ZeroNumberPosition *zeroNumberPosition) {
    (*zeroNumberPosition).zero_down = number->height + 1 == zero->height && number->width == zero->width;
    (*zeroNumberPosition).zero_left = number->height == zero->height && number->width == zero->width + 1;
    (*zeroNumberPosition).zero_right = number->height == zero->height && number->width == zero->width - 1;
    (*zeroNumberPosition).zero_up = number->height - 1 == zero->height && number->width == zero->width;
}

static void hydrate_target_zero_position(const Point *target, const Point *zero, TargetZeroPosition *targetZeroPosition) {
    (*targetZeroPosition).target_left = target->width < zero->width;
    (*targetZeroPosition).target_right = target->width > zero->width;
    (*targetZeroPosition).target_up = target->height < zero->height;
    (*targetZeroPosition).target_down = target->height > zero->height;
}

static void do_walk_zero_around(uint8 **board, Point *zero, EnumDirection direction) {
    if (direction == DIRECTION_UP) {
        if (zero->width < BOARD_WIDTH - 1 && zero->height - 1 > 0) {
            number_go_direction(board, zero, DIRECTION_RIGHT);
            number_go_direction(board, zero, DIRECTION_UP);
            number_go_direction(board, zero, DIRECTION_UP);
            number_go_direction(board, zero, DIRECTION_LEFT);
        } else {
            number_go_direction(board, zero, DIRECTION_LEFT);
            number_go_direction(board, zero, DIRECTION_UP);
            number_go_direction(board, zero, DIRECTION_UP);
            number_go_direction(board, zero, DIRECTION_RIGHT);
        }
    }
    if (direction == DIRECTION_LEFT) {
        if (zero->height < BOARD_HEIGHT - 1 && zero->width - 1 > 0) {
            number_go_direction(board, zero, DIRECTION_DOWN);
            number_go_direction(board, zero, DIRECTION_LEFT);
            number_go_direction(board, zero, DIRECTION_LEFT);
            number_go_direction(board, zero, DIRECTION_UP);
        } else {
            number_go_direction(board, zero, DIRECTION_UP);
            number_go_direction(board, zero, DIRECTION_LEFT);
            number_go_direction(board, zero, DIRECTION_LEFT);
            number_go_direction(board, zero, DIRECTION_DOWN);
        }
    }

    if (direction == DIRECTION_RIGHT) {
        if (zero->height < BOARD_HEIGHT - 1 && zero->width - 1 > 0) {
            number_go_direction(board, zero, DIRECTION_DOWN);
            number_go_direction(board, zero, DIRECTION_RIGHT);
            number_go_direction(board, zero, DIRECTION_RIGHT);
            number_go_direction(board, zero, DIRECTION_UP);
        } else {
            number_go_direction(board, zero, DIRECTION_UP);
            number_go_direction(board, zero, DIRECTION_RIGHT);
            number_go_direction(board, zero, DIRECTION_RIGHT);
            number_go_direction(board, zero, DIRECTION_DOWN);
        }
    }

    if (direction == DIRECTION_DOWN) {
        if (zero->width < BOARD_WIDTH - 1 && zero->height - 1 > 0) {
            number_go_direction(board, zero, DIRECTION_RIGHT);
            number_go_direction(board, zero, DIRECTION_DOWN);
            number_go_direction(board, zero, DIRECTION_DOWN);
            number_go_direction(board, zero, DIRECTION_LEFT);
        } else {
            number_go_direction(board, zero, DIRECTION_LEFT);
            number_go_direction(board, zero, DIRECTION_DOWN);
            number_go_direction(board, zero, DIRECTION_DOWN);
            number_go_direction(board, zero, DIRECTION_RIGHT);
        }
    }
}
