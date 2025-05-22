/*
** EPITECH PROJECT, 2024
** modify_file
** File description:
** functions to modify content of the file
*/

#include "../include/bitmap.h"
void set_line(color_rgb_t color, int pos_y, bitmap_file_t file)
{
    if (pos_y < 0 || pos_y > file.info_header.height)
        return;
    for (int x = 0; x <= file.info_header.width; x++) {
        file.content[pos_y][x] = color;
    }
}

void color_inversion_effect(color_rgb_t **content, int size_x, int size_y)
{
    for (int y = 0; y < size_y; y++) {
        for (int x = 0; x < size_x; x++) {
            content[y][x].blue = ~(content[y][x].blue);
            content[y][x].green = ~(content[y][x].green);
            content[y][x].red = ~(content[y][x].red);
        }
    }
}

void modify_file(color_rgb_t **content, int size_x, int size_y)
{
    color_inversion_effect(content, size_x, size_y);
}
