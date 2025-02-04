// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
#include <stdbool.h>
#include <png.h>
#include "color.h"
#include "image.h"
#include "executor.h"

int main(int argc, char** argv) {
	ImageData image = read_image_file(argc, argv[1]);
	Block blocks[image.height][image.width];
	processImage(image.height, image.width, blocks, &image);

	// for(int y = 0; y < image.height; y++) {
	// 	for(int x = 0; x < image.width; x++) {
	// 		printf("%2s ", blocks[y][x].name);
	// 	}
	// 	printf("\n");
	// }

    execute(image.height, image.width, blocks);

	free_image_data(&image);

	return 0;
}



