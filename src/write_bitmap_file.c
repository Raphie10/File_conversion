/*
** EPITECH PROJECT, 2024
** write_bitmap_file
** File description:
** functions to write a bitmap file
*/

#include "../include/bitmap.h"
#include <stdio.h>
void write_bitmap_file(bitmap_file_t file)
{
    FILE *output = fopen("testfile.bmp", "wb");
    int zero = 0;
    const char *magic_word = "BM";

    fwrite(magic_word, sizeof(char), MAGIC_WORD_SIZE, output);
    fwrite(&file.file_header, sizeof(bitmap_file_header_t), 1, output);
    fwrite(&(file.info_header), file.info_header.info_header_size, 1, output);
    for (int i = 0; i < file.info_header.height; i++) {
        fwrite(file.content[i], RGB_SIZE, file.info_header.width, output);
        fwrite(&zero, GET_PADDING(file.info_header.width), 1, output);
    }
    fclose(output);
}
