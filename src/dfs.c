#include "dfs.h"
#include <string.h>

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
int is_equal(Block block1, Block block2) {
    return (strcmp(block1.name, block2.name) == 0);
}

int is_valid(int y, int x, int height, int width, int visited[height][width],
             Block blocks[height][width], Block block) {
    return (y >= 0 && y < height && x >= 0 && x < width &&
            is_equal(blocks[y][x], block) && !visited[y][x]);
}

int dfs(int y, int x, int height, int width, int visited[height][width],
        Block blocks[height][width], Block block, Point *furthest,
        int direction) {
    if (!is_valid(y, x, height, width, visited, blocks, block))
        return 0;

    visited[y][x] = 1;
    int count = 1;

    // Update furthest block based on DP direction
    if ((direction == 1 && x > furthest->x) || // Right
        (direction == 2 && y > furthest->y) || // Bottom
        (direction == 3 && x < furthest->x) || // Left
        (direction == 4 && y < furthest->y)) { // Up
        furthest->x = x;
        furthest->y = y;
    }

    for (int i = 0; i < 4; i++) {
        count += dfs(y + dy[i], x + dx[i], height, width, visited, blocks,
                     block, furthest, direction);
    }

    return count;
}
