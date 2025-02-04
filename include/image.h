#pragma once
#include "color.h"

typedef struct {
    int width;
    int height;
    RGB** pixels;
} ImageData;

ImageData read_image_file(int argc, const char *filename);
void processImage(int height, int width, Block blocks[height][width], ImageData *image);
void free_image_data(ImageData *image);

