/*
** EPITECH PROJECT, 2024
** generate_png_file
** File description:
** file to generate a png file
*/

#include "bitmap.h"
#include <stdio.h>
void generate_png_file(void)
{
    char magic_word[] = {137, 80, 78, 71, 13, 10, 26, 10};

    FILE *file = fopen("testfile.png", "wb");

    fwrite(file, sizeof(magic_word), 1, file);
    
}