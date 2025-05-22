/*
** EPITECH PROJECT, 2024
** Amazed
** File description:
** Main function
*/
#include <stdio.h>
#include "../include/bitmap.h"
#include "../include/png.h"
#include "../include/convert_file.h"
#include <string.h>

void free_content(color_rgb_t ***content, int height)
{
    for (int i = 0; i < height; i++) {
        free((*content)[i]);
    }
    free(*content);
}

int main(int argc, char **argv)
{
    bitmap_file_t file;
    png_file_t png_file;
    if (argc == 1) {
        file = generate_blank_bitmap_file(1000, 1000, 40);
    } else {
        file = get_bitmap_file(argv[1]);
        if (!file.content)
            file = generate_blank_bitmap_file(1000, 1000, 40);
    }
    png_file = convert_bmp_file_to_png_file(file);
    write_png_file("testfile.png", png_file);
    // modify_file(file.content, file.info_header.width, file.info_header.height);
    // write_bitmap_file(file);
    // generate_png_file();
    // free_content(&file.content, file.info_header.height);
    return 0;
}
