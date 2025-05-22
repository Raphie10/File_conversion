/*
** EPITECH PROJECT, 2024
** generate_png_file
** File description:
** file to generate a png file
*/

#include "../include/png.h"
#include "../include/convert_file.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


png_image_header_chunk_t generate_png_header_chunk_data(void)
{
    png_image_header_chunk_t header_chunk_data;

    header_chunk_data.width = 10;
    header_chunk_data.height = 10;
    header_chunk_data.bit_depth = 8;
    header_chunk_data.color_type = 6;
    header_chunk_data.compression_method = 0;
    header_chunk_data.filter_method = 0;
    header_chunk_data.interlace_method = 0;
    return header_chunk_data;
}

scanline_t create_empty_scanline(unsigned int length)
{
    scanline_t scanline;

    scanline.filter = 0;
    color_rgba_t *data = malloc(sizeof(color_rgba_t) * length);
    for (unsigned int i = 0; i < length; i++) {
        data[i] = (color_rgba_t){255, 255, 255, 255};
    }
    scanline.data = data;
    return scanline;
}

color_rgba_t **generate_blank_rgba_content(int width, int height)
{
    color_rgba_t **content = malloc(sizeof(color_rgba_t *) * height);

    for (int i = 0; i < height; i++) {
        content[i] = malloc(sizeof(color_rgba_t) * width);
        for (int j = 0; j < width; j++) {
            content[i][j] = (color_rgba_t){255, 255, 255, 0};
        }
    }
    return content;
}

void generate_png_file(void)
{
    png_image_header_chunk_t header = generate_png_header_chunk_data();
    color_rgba_t color = {255, 255, 255, 0};
    color_rgba_t red = {255, 0, 0, 255};
    color_rgba_t **content = generate_blank_rgba_content(header.width, header.height);

    content[0][0] = red;
    scanline_t *scanline = convert_pixel_array_to_scan_lines(content, header.width, header.height);
    for (unsigned int i = 0; i < header.height; i++) {
        scanline[i] = create_empty_scanline(header.width);
    }
    png_file_t png_file = {header, scanline};
    write_png_file("testfile.png", png_file);
}
