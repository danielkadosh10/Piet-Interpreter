#include "executor.h"
#include "dfs.h"
#include <stdio.h>
#include <string.h>

void execute(int height, int width, Block blocks[height][width])
{
    Stack *stack = init_stack(2);
    DP dp = {1, {0, 0}};
    CC cc = {3}; 
    int repeat = 0;
    Edge old_edge = {0, {0, 0}};
    

    // Scrap entire thing try to find edge using dfs

    while(repeat == 0)
    // for (int i = 0; i < 300; i++)
    {
        Edge edge = find_edge(height, width, blocks, &dp);
        dp.location = edge.point;
        action(edge, old_edge, &dp, &cc, stack, height, width, blocks);

        Point next_edge = next_color_block(height, width, blocks, &dp, &cc, edge);

        repeat = check_wall(edge, next_edge, &dp, &cc, height, width, blocks);

        old_edge = edge;
    }
    printf("\n");
}

Edge find_edge(int height, int width, Block blocks[height][width], DP *dp) 
{
    int visited[height][width];
    memset(visited, 0, sizeof(visited));

    Point furthest = {dp->location.x, dp->location.y};
    int count = dfs(dp->location.y, dp->location.x, height, width, visited, blocks, 
                    blocks[dp->location.y][dp->location.x], &furthest, dp->direction);
    
    Edge result = {count, furthest};
    return result;
}

Point next_color_block(int height, int width, Block blocks[height][width], DP *dp, CC *cc, Edge edge)
{
    Block edge_codel = blocks[dp->location.y][dp->location.x];
    Point next_point = {0, 0};

    // DP points right or left
    if (dp->direction==RIGHT || dp->direction==LEFT)
    {
        Point up_codel = {dp->location.x, dp->location.y};
        Point down_codel = {dp->location.x, dp->location.y};

        // Going Up
        while (up_codel.y > 0 && strcmp(blocks[up_codel.y - 1][up_codel.x].name, edge_codel.name) == 0)
        {
            up_codel.y--;
        }
        
        // Going Down
        while (down_codel.y + 1 < height && strcmp(blocks[down_codel.y + 1][down_codel.x].name, edge_codel.name) == 0)
        {
            down_codel.y++;
        }

        if (dp->direction==RIGHT)
        {
            if (cc->direction==RIGHT) 
            {
                next_point.x = down_codel.x + 1;
                next_point.y = down_codel.y;
            }
            else 
            {
                next_point.x = up_codel.x + 1;
                next_point.y = up_codel.y;
            }
        }
        else 
        {
            if (cc->direction==RIGHT) 
            {
                next_point.x = up_codel.x - 1;
                next_point.y = up_codel.y;
            }
            else 
            {
                next_point.x = down_codel.x - 1;
                next_point.y = down_codel.y;
            }
            
        }
    }
   
    // DP points down or up
    if (dp->direction==DOWN || dp->direction==UP)
    {
        Point right_codel = {dp->location.x, dp->location.y};
        Point left_codel = {dp->location.x, dp->location.y};

        // Going Right
        while (right_codel.x < width - 1 && strcmp(blocks[right_codel.y][right_codel.x + 1].name, edge_codel.name) == 0)
        {
            right_codel.x++;
        }
        
        // Going Left
        while (left_codel.x > 0 && strcmp(blocks[left_codel.y][left_codel.x - 1].name, edge_codel.name) == 0)
        {
            left_codel.x--;
        }
    
        if (dp->direction==DOWN)
        {
            if (cc->direction==RIGHT) 
            {
                next_point.x = left_codel.x;
                next_point.y = left_codel.y + 1;
            }
            else 
            {
                next_point.x = right_codel.x;
                next_point.y = right_codel.y + 1;
            }
        }
        else
        {
            if (cc->direction==RIGHT) 
            {
                next_point.x = right_codel.x;
                next_point.y = right_codel.y - 1;
            }
            else 
            {
                next_point.x = left_codel.x;
                next_point.y = left_codel.y - 1;
            }
        }
    }

    return next_point;
}

void action(Edge edge, Edge old_edge, DP *dp, CC *cc, Stack *stack, int height, int width, Block blocks[height][width])
{
    int oldx = old_edge.point.x;
    int oldy = old_edge.point.y;
    int x = edge.point.x;
    int y = edge.point.y;

    if (strcmp(blocks[y][x].name, blocks[oldy][oldx].name) == 0) return;
    if (strcmp(blocks[y][x].name, "WH") == 0) return;
    if (strcmp(blocks[oldy][oldx].name, "WH") == 0) return;

    int hue_change = (blocks[y][x].hue - blocks[oldy][oldx].hue + 6) % 6;
    int lightness_change = (blocks[y][x].lightness 
        - blocks[oldy][oldx].lightness + 3) % 3;
    Operation op = get_operation(hue_change, lightness_change);
    // printf("Old %s, New %s ", blocks[oldy][oldx].name, blocks[y][x].name);
    // printf("Lightness %d, %d ", blocks[y][x].lightness, blocks[oldy][oldx].lightness);
    // printf("Hue %d, %d ", blocks[y][x].hue, blocks[oldy][oldx].hue);

    switch (op) {
        case OP_PUSH: push(stack, old_edge.value); break;
        case OP_POP: pop(stack); break;
        case OP_ADD: add(stack); break;
        case OP_SUBTRACT: subtract(stack); break;
        case OP_MULTIPLY: multiply(stack); break;
        case OP_DIVIDE: divide(stack); break;
        case OP_MOD: mod(stack); break;
        case OP_NOT: not(stack); break;
        case OP_GREATER: greater(stack); break;
        case OP_POINTER: pointer(stack, dp); break;
        case OP_SWITCH: swap(stack, cc); break;
        case OP_DUPLICATE: duplicate(stack); break;
        case OP_ROLL: roll(stack); break;
        case OP_IN_NUMBER: in_num(stack); break;
        case OP_IN_CHAR: in_char(stack); break;
        case OP_OUT_NUMBER: out_num(stack); break;
        case OP_OUT_CHAR: out_char(stack); break;
        default: break;
    }
}

int check_wall(Edge edge, Point next_point, DP *dp, CC *cc, int height, int width, Block blocks[height][width])
{
    int attempts = 0;

    while (attempts < 8) 
    {
        // Check if next_point is out of bounds or a black block
        if (next_point.x < 0 || next_point.x >= width ||
            next_point.y < 0 || next_point.y >= height ||
            strcmp(blocks[next_point.y][next_point.x].name, "BL") == 0) 
        {

            if (attempts % 2 == 0)
                cc->direction ^= 2;
            else
            {
                dp->direction = (dp->direction == 4) ? 1 : dp->direction + 1;
            }

            // Recalculate next_point based on new DP and CC
            dp->location = find_edge(height, width, blocks, dp).point;
            next_point = next_color_block(height, width, blocks, dp, cc, edge);

            attempts++;
        } 
        else 
        {
            // Found a valid move
            dp->location = next_point;  // Update DP's location
            return 0; // Successfully moved, exit function
        }
    }

    // If all 8 attempts failed, terminate the program
    // printf("Program terminated: No valid move found.\n");
    return -1; // Indicate failure
}

Operation get_operation(int hue_change, int lightness_change) {
    switch (hue_change) {
        case 0:
            return (lightness_change == 0) ? OP_NONE : (lightness_change == 1) ? OP_PUSH : OP_POP;
        case 1:
            return (lightness_change == 0) ? OP_ADD : (lightness_change == 1) ? OP_SUBTRACT : OP_MULTIPLY;
        case 2:
            return (lightness_change == 0) ? OP_DIVIDE : (lightness_change == 1) ? OP_MOD : OP_NOT;
        case 3:
            return (lightness_change == 0) ? OP_GREATER : (lightness_change == 1) ? OP_POINTER : OP_SWITCH;
        case 4:
            return (lightness_change == 0) ? OP_DUPLICATE : (lightness_change == 1) ? OP_ROLL : OP_IN_NUMBER;
        case 5:
            return (lightness_change == 0) ? OP_IN_CHAR : (lightness_change == 1) ? OP_OUT_NUMBER : OP_OUT_CHAR;
        default:
            return OP_NONE;
    }
}

