#pragma once
#include <string.h>
#include "image.h"
#include "executor.h"
#include "color.h"

int is_equal(Block block1, Block block2);
int is_valid(int y, int x, int height, int width, int visited[height][width], Block blocks[height][width], Block block);
int dfs(int x, int y, int height, int width, int visited[height][width],
        Block blocks[height][width], Block block, Point *furthest, int direction);
