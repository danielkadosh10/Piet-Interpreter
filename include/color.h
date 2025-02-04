#pragma once

#define MAX_COLORS 20

typedef struct {
	char* name;
    enum {
        LIGHT,
        NORMAL,
        DARK
    } lightness;
	enum {
		RED,
		YELLOW,
		GREEN,
		CYAN,
		BLUE,
		MAGENTA,
		WHITE,
		BLACK,
	} hue;
} Block;

typedef struct {
	int r;
	int g;
	int b;
	int x;
	int y;
} RGB;

typedef struct {
	Block block;
	int r;
	int g;
	int b;
} ColorMapping;

extern ColorMapping map[];

Block getColorBlock(int r, int g, int b);
