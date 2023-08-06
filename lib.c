#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define TARGET_WIDTH 8
#define TARGET_HEIGHT 8
#define TARGET_CHANNELS 1

uint64_t imageHash(const char *path) {
    // load image
    int width, height, channels;
    unsigned char *image_data = stbi_load(path, &width, &height, &channels, 0);
    if (!image_data) {
        fprintf(stderr, "Error loading image\n");
        return 1;
    }
    // resize the image
    unsigned char *resized_image_data = malloc(TARGET_WIDTH * TARGET_HEIGHT * channels);
    stbi_image_free (image_data);
    stbir_resize_uint8(image_data, width, height, 0, resized_image_data, TARGET_WIDTH, TARGET_HEIGHT, 0, channels);
    if (!stbi_write_jpg("resize.jpeg", TARGET_WIDTH, TARGET_HEIGHT, channels, resized_image_data, 100)) {
        fprintf(stderr, "Error writing image\n");
        return 1;
    }
    
    // turn the image to grayscale
    unsigned char *gray_image_data = malloc(TARGET_WIDTH * TARGET_HEIGHT * TARGET_CHANNELS);
    uint64_t sum = 0;
    for (int i = 0; i < TARGET_WIDTH * TARGET_HEIGHT; i++) {
        gray_image_data[i] = resized_image_data[i * channels];
    }
    free(resized_image_data);
    resized_image_data = NULL;

    for (int i = 0; i < TARGET_WIDTH * TARGET_HEIGHT; i++) {
        sum += gray_image_data[i];
    }

    uint64_t average = sum / (TARGET_WIDTH * TARGET_HEIGHT);
    uint64_t hash = 0;
    for (int i = 0; i < TARGET_WIDTH * TARGET_HEIGHT; i++) {
        if (gray_image_data[i] > average) {
            hash |= 1 << i;
        }
    }

    if (!stbi_write_jpg("grey.jpeg", TARGET_WIDTH, TARGET_HEIGHT, TARGET_CHANNELS, gray_image_data, 100)) {
        fprintf(stderr, "Error writing image\n");
        return 1;
    }
    free(gray_image_data);
    gray_image_data = NULL;
    return hash;
}

