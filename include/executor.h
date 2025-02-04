#pragma once

#include "color.h"
#include "stack.h"
#include "dp.h"

#define RIGHT 1
#define DOWN 2
#define LEFT 3
#define UP 4


typedef enum {
    OP_NONE, OP_PUSH, OP_POP, 
    OP_ADD, OP_SUBTRACT, OP_MULTIPLY,
    OP_DIVIDE, OP_MOD, OP_NOT, 
    OP_GREATER, OP_POINTER, OP_SWITCH, 
    OP_DUPLICATE, OP_ROLL, OP_IN_NUMBER,
    OP_IN_CHAR, OP_OUT_NUMBER, OP_OUT_CHAR,
} Operation;

void execute(int height, int width, Block blocks[height][width]);
Edge find_edge(int height, int width, Block blocks[height][width], DP *dp);
Point next_color_block(int height, int width, Block blocks[height][width],
                       DP *dp, CC *cc, Edge edge);
void action(Edge edge, Edge old_edge, DP *dp, CC *cc, Stack *stack, int height, int width, Block blocks[height][width]);
int check_wall(Edge edge, Point next_point, DP *dp, CC *cc, int height,
               int width, Block blocks[height][width]);
Operation get_operation(int hue_change, int lightness_change);
