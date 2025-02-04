#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <png.h>
#include <gif_lib.h>
#include <strings.h>
#include "image.h"
#include "color.h"

// Function to determine the image format
static const char *get_file_extension(const char *filename) {
    const char *ext = strrchr(filename, '.');
    return (ext) ? ext + 1 : "";
}

// Read PNG file
static ImageData read_png_file(const char *filename) {
    ImageData image = {0, 0, NULL};

    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        perror("Failed to open file");
        return image;
    }

    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png) {
        fclose(fp);
        return image;
    }

    png_infop info = png_create_info_struct(png);
    if (!info) {
        png_destroy_read_struct(&png, NULL, NULL);
        fclose(fp);
        return image;
    }

    png_init_io(png, fp);
    png_read_info(png, info);

    int width = png_get_image_width(png, info);
    int height = png_get_image_height(png, info);
    png_byte color_type = png_get_color_type(png, info);
    png_byte bit_depth = png_get_bit_depth(png, info);

    if ((color_type != PNG_COLOR_TYPE_RGB && color_type != PNG_COLOR_TYPE_RGBA) || (bit_depth != 8 && bit_depth != 32)) {
        fprintf(stderr, "Unsupported color type or bit depth\n");
        png_destroy_read_struct(&png, &info, NULL);
        fclose(fp);
        return image;
    }

    int bytes_per_pixel = (color_type == PNG_COLOR_TYPE_RGBA) ? 4 : 3;

    image.width = width;
    image.height = height;
    image.pixels = (RGB**)malloc(height * sizeof(RGB*));
    for (int y = 0; y < height; y++) {
        image.pixels[y] = (RGB*)malloc(width * sizeof(RGB));
    }

    png_bytep *row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * height);
    for (int y = 0; y < height; y++) {
        row_pointers[y] = (png_byte *)malloc(png_get_rowbytes(png, info));
    }

    png_read_image(png, row_pointers);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            png_bytep pixel = &(row_pointers[y][x * bytes_per_pixel]);
            image.pixels[y][x].r = pixel[0];
            image.pixels[y][x].g = pixel[1];
            image.pixels[y][x].b = pixel[2];
        }
    }

    for (int y = 0; y < height; y++) {
        free(row_pointers[y]);
    }
    free(row_pointers);

    png_destroy_read_struct(&png, &info, NULL);
    fclose(fp);

    return image;
}

// Read GIF file
static ImageData read_gif_file(const char *filename) {
    ImageData image = {0, 0, NULL};

    int error;
    GifFileType *gif = DGifOpenFileName(filename, &error);
    if (!gif) {
        fprintf(stderr, "Failed to open GIF file: %s\n", filename);
        return image;
    }

    if (DGifSlurp(gif) != GIF_OK) {
        fprintf(stderr, "Failed to read GIF data\n");
        DGifCloseFile(gif, &error);
        return image;
    }

    image.width = gif->SWidth;
    image.height = gif->SHeight;
    image.pixels = (RGB**)malloc(image.height * sizeof(RGB*));
    for (int y = 0; y < image.height; y++) {
        image.pixels[y] = (RGB*)malloc(image.width * sizeof(RGB));
    }

    SavedImage *frame = &gif->SavedImages[0]; // Taking the first frame for static GIF
    ColorMapObject *colorMap = (gif->SColorMap) ? gif->SColorMap : gif->Image.ColorMap;

    if (!colorMap) {
        fprintf(stderr, "No color map found in GIF\n");
        free_image_data(&image);
        DGifCloseFile(gif, &error);
        return image;
    }

    for (int y = 0; y < image.height; y++) {
        for (int x = 0; x < image.width; x++) {
            int index = frame->RasterBits[y * image.width + x];
            if (index < colorMap->ColorCount) {
                GifColorType color = colorMap->Colors[index];
                image.pixels[y][x].r = color.Red;
                image.pixels[y][x].g = color.Green;
                image.pixels[y][x].b = color.Blue;
            }
        }
    }

    DGifCloseFile(gif, &error);
    return image;
}

// Wrapper function to read an image file (PNG or GIF)
ImageData read_image_file(int argc, const char *filename) {
    if (argc < 2) {
        printf("Please provide a file\n");
        exit(1);
    }

    const char *ext = get_file_extension(filename);
    if (strcasecmp(ext, "png") == 0) {
        return read_png_file(filename);
    } else if (strcasecmp(ext, "gif") == 0) {
        return read_gif_file(filename);
    } else {
        fprintf(stderr, "Unsupported file format: %s\n", ext);
        exit(1);
    }
}

// Process the image and map it to blocks
void processImage(int height, int width, Block blocks[height][width], ImageData *image) {
    if (image->pixels) {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                RGB rgb = image->pixels[y][x];
                blocks[y][x] = getColorBlock(rgb.r, rgb.g, rgb.b);
            }
        }
    }
}

// Free allocated image data
void free_image_data(ImageData *image) {
    if (image->pixels) {
        for (int y = 0; y < image->height; y++) {
            free(image->pixels[y]);
        }
        free(image->pixels);
    }
}

