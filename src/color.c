#include <stdio.h>
#include <stdlib.h>
#include <png.h>
#include "color.h"


ColorMapping map[] = {
	{{"LR", LIGHT, RED}, 		255, 192, 192},
	{{"LY", LIGHT, YELLOW}, 	255, 255, 192},
	{{"LG", LIGHT, GREEN}, 		192, 255, 192},
	{{"LC", LIGHT, CYAN}, 		192, 255, 255},
	{{"LB", LIGHT, BLUE}, 		192, 192, 255},
	{{"LM", LIGHT, MAGENTA}, 	255, 192, 255},
	{{"R", NORMAL, RED}, 		255, 0, 0},
	{{"Y", NORMAL, YELLOW}, 	255, 255, 0},
	{{"G", NORMAL, GREEN}, 		0, 255, 0},
	{{"C", NORMAL, CYAN}, 		0, 255, 255},
	{{"B", NORMAL, BLUE}, 		0, 0, 255},
	{{"M", NORMAL, MAGENTA}, 	255, 0, 255},
	{{"DR", DARK, RED}, 		192, 0, 0},
	{{"DY", DARK, YELLOW}, 		192, 192, 0},
	{{"DG", DARK, GREEN}, 		0, 192, 0},
	{{"DC", DARK, CYAN}, 		0, 192, 192},
	{{"DB", DARK, BLUE}, 		0, 0, 192},
	{{"DM", DARK, MAGENTA}, 	192, 0, 192},
	{{"BL", NORMAL, BLACK}, 	0, 0, 0},
	{{"WH", NORMAL, WHITE}, 	255, 255, 255},
};


Block getColorBlock(int r, int g, int b)
{
	for(int i = 0; i < MAX_COLORS; i++) {
		if (r == map[i].r && g == map[i].g && b == map[i].b)
			return map[i].block;
	}
	return map[MAX_COLORS - 1].block;
}
