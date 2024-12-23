/*
** EPITECH PROJECT, 2024
** read_content.c
** File description:
** file to read the content from a bmp file
*/

#include "../include/bitmap.h"
#include <stdio.h>
#include <string.h>
void print_header(char *filename)
{
    FILE *file = fopen(filename, "r");
    bitmap_file_header_t file_header;
    bitmap_info_header_t info_header;

    char beg[2];
    fread(beg, 1, 2, file);
    fread(&file_header, sizeof(bitmap_file_header_t), 1, file);
    fread(&info_header, sizeof(bitmap_info_header_t), 1, file);

    printf("File Header for %s: \nprog_size = \t%d, \nreserved = \t%d, \ndata_offset = \t%d", filename, file_header.prog_size, file_header.reserved, file_header.data_offset);
    printf("\n\nInfo Header: \ninfo_header_size = \t%d, \nwidth =           \t%d, \nheight =           \t%d, \nplane =               \t%d, \nbits_per_pixel = \t%d, \ncompression =    \t%d, \nimage_size =      \t%d, \nx_pixels_per_meter = \t%d, \ny_pixels_per_meter = \t%d, \ncolors_used =     \t%d, \nimportant_colors = \t%d\n\n\n",
    info_header.info_header_size,
    info_header.width,
    info_header.height,
    info_header.plane,
    info_header.bits_per_pixel,
    info_header.compression,
    info_header.image_size,
    info_header.x_pixels_per_meter,
    info_header.y_pixels_per_meter,
    info_header.colors_used,
    info_header.important_colors);
}

int read_file_header(char *filename, FILE *file, bitmap_file_t *file_output)
{
    char beg[2];

    if (fread(beg, 1, MAGIC_WORD_SIZE, file) != MAGIC_WORD_SIZE || strncmp(beg, MAGIC_WORD, MAGIC_WORD_SIZE)) {
        printf("%s: Is not a bitmap file\n", filename);
        return 0;
    }
    if (!fread(&file_output->file_header, sizeof(bitmap_file_header_t), 1, file)) {
        printf("%s: Failed to read file header\n", filename);
        return 0;
    }
    return 1;
}

int read_info_header(char *filename, FILE *file, bitmap_file_t *file_output)
{
    int header_size;

    if (!fread(&header_size, sizeof(int), 1, file)) {
        printf("%s: Failed to read info header size\n", filename);
        return 0;
    }
    if (header_size != 40 &&
        header_size != 52 &&
        header_size != 56 &&
        header_size != 108 &&
        header_size != 124) {
            printf("%s: Invalid header size of %d\n", filename, header_size);
            return 0;
    }
    fseek(file, 14, SEEK_SET);
    if (!fread(&file_output->info_header, header_size, 1, file)) {
        printf("%s: Failed to read info header\n", filename);
        return 0;
    }
    return 1;
}

int read_content(char *filename, FILE *file, bitmap_file_t *file_output)
{
    int height = file_output->info_header.height;
    int width = file_output->info_header.width;
    char zero[4];

    file_output->content = malloc(sizeof(color_t *) * (height + 1));
    for (int i = 0; i < height; i++) {
        file_output->content[i] = malloc(sizeof(color_t) * width);
        size_t read = fread(file_output->content[i], sizeof(color_t), width, file);
        if (read != width) {
            printf("%s: Failed to read data\n", filename);
            file_output->content = NULL;
            return 0;
        }
        fread(zero, GET_PADDING(width), 1, file);
    }
    return 1;
}

bitmap_file_t get_file(char *filename)
{
    FILE *file = fopen(filename, "r");
    bitmap_file_t file_output = {.content = NULL};

    if (!file) {
        printf("%s: File not found\n", filename);
        return file_output;
    }
    if (!read_file_header(filename, file, &file_output))
        return file_output;
    if (!read_info_header(filename, file, &file_output))
        return file_output;
    if (!read_content(filename, file, &file_output))
        file_output.content = NULL;
    return file_output;
}
