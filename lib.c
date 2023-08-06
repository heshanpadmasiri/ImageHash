#include "lib.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
uint64_t imageHash(const char *path) {
    int width, height, channels;
    unsigned char *image_data = stbi_load(path, &width, &height, &channels, 0);
    if (!image_data) {
        fprintf(stderr, "Error loading image\n");
        return 1;
    }

    printf("Image resolution: %d x %d\n", width, height);

    stbi_image_free (image_data);
    return 0;
}
