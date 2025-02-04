#pragma once

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    int direction; // 1->right 2->down 3->left 4->up
    Point location;
} DP;

typedef struct {
    int direction; // 1->right 3->left
} CC;

typedef struct {
    int value;
    Point point;
} Edge;
