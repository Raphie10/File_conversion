/*
** EPITECH PROJECT, 2024
** Amazed
** File description:
** Main function
*/
#include <stdio.h>
#include "../include/bitmap.h"
#include <string.h>

void write_bitmap_file(bitmap_file_t file)
{
    FILE *output = fopen("testfile.bmp", "wb");
    int zero = 0;
    const char *magic_word = "BM";

    fwrite(magic_word, sizeof(char), MAGIC_WORD_SIZE, output);
    fwrite(&file.file_header, sizeof(bitmap_file_header_t), 1, output);
    fwrite(&(file.info_header), file.info_header.info_header_size, 1, output);
    for (int i = 0; i < file.info_header.height; i++) {
        fwrite(file.content[i], sizeof(color_t), file.info_header.width, output);
        fwrite(&zero, GET_PADDING(file.info_header.width), 1, output);
    }
    fclose(output);
}

void free_content(color_t ***content, int height)
{
    for (int i = 0; i < height; i++) {
        free((*content)[i]);
    }
    free(*content);
}

void set_line(color_t color, int pos_y, bitmap_file_t file)
{
    if (pos_y < 0 || pos_y > file.info_header.height)
        return;
    for (int x = 0; x <= file.info_header.width; x++) {
        file.content[pos_y][x] = color;
    }
}

void color_inversion_effect(color_t **content, int size_x, int size_y)
{
    for (int y = 0; y < size_y; y++) {
        for (int x = 0; x < size_x; x++) {
            content[y][x].blue = ~(content[y][x].blue);
            content[y][x].green = ~(content[y][x].green);
            content[y][x].red = ~(content[y][x].red);
        }
    }
}

void modify_file(color_t **content, int size_x, int size_y)
{
    color_inversion_effect(content, size_x, size_y);
}

int main(int argc, char **argv)
{
    bitmap_file_t file;
    if (argc == 1) {
        file = generate_blank_file(1000, 1000, 40);
    } else {
        file = get_file(argv[1]);
        if (!file.content)
            file = generate_blank_file(1000, 1000, 40);
    }
    modify_file(file.content, file.info_header.width, file.info_header.height);
    write_bitmap_file(file);
    free_content(&file.content, file.info_header.height);
}
