/*
** EPITECH PROJECT, 2024
** read_bitmap_content.c
** File description:
** file to read the content from a bmp file
*/

#include "../include/bitmap.h"
#include <stdio.h>
#include <string.h>

int read_bitmap_file_header(
    char *filename,
    FILE *file,
    bitmap_file_t *file_output)
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

int read_bitmap_info_header(
    char *filename,
    FILE *file,
    bitmap_file_t *file_output)
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

int read_bitmap_content(char *filename, FILE *file, bitmap_file_t *file_output)
{
    int height = file_output->info_header.height;
    int width = file_output->info_header.width;
    char zero[4];

    file_output->content = malloc(sizeof(color_rgb_t *) * (height + 1));
    for (int i = 0; i < height; i++) {
        file_output->content[i] = malloc(RGB_SIZE * width);
        fread(file_output->content[i], RGB_SIZE, width, file);
        fread(zero, GET_PADDING(width), 1, file);
    }
    return 1;
}

bitmap_file_t get_bitmap_file(char *filename)
{
    FILE *file = fopen(filename, "r");
    bitmap_file_t file_output = {.content = NULL};

    if (!file) {
        printf("%s: File not found\n", filename);
        return file_output;
    }
    if (!read_bitmap_file_header(filename, file, &file_output))
        return file_output;
    if (!read_bitmap_info_header(filename, file, &file_output))
        return file_output;
    if (!read_bitmap_content(filename, file, &file_output))
        file_output.content = NULL;
    return file_output;
}
