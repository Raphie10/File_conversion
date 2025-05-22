/*
** EPITECH PROJECT, 2025
** convert bitmap to png
** File description:
** file to convert bitmap to png files
*/

#include "../include/png.h"
#include "../include/convert_file.h"
#include "../include/bitmap.h"

png_image_header_chunk_t convert_bmp_header_to_png_header(bitmap_info_header_t bmp_header)
{
    png_image_header_chunk_t png_header;

    png_header.width = bmp_header.width;
    png_header.height = bmp_header.height;
    switch (bmp_header.bits_per_pixel) {
        case 1:
        case 2:
        case 4:
        case 8:
        case 16:
        case 24:
            png_header.bit_depth = 8;
            break;
        case 32:
            png_header.bit_depth = 8;
            break;
        default:
            png_header.bit_depth = 8;
            break;
    }
    png_header.color_type = 6;
    png_header.compression_method = 0;
    png_header.filter_method = 0;
    png_header.interlace_method = 0;
    return png_header;
}

color_rgba_t **convert_rgb_to_rgba(color_rgb_t **content, int width, int height)
{
    color_rgba_t **new_content = malloc(sizeof(color_rgba_t *) * height);

    for (int i = 0; i < height; i++) {
        new_content[i] = malloc(sizeof(color_rgba_t) * width);
        for (int j = 0; j < width; j++) {
            new_content[i][j].red = content[i][j].red;
            new_content[i][j].green = content[i][j].green;
            new_content[i][j].blue = content[i][j].blue;
            new_content[i][j].alpha = 255;
        }
    }
    return new_content;
}

scanline_t *convert_pixel_array_to_scan_lines(color_rgba_t **content, int width, int height)
{
    scanline_t *scanlines = malloc(sizeof(scanline_t) * height);

    for (int i = 0; i < height; i++) {
        scanlines[i].filter = 0;
        scanlines[i].data = content[i];
    }
    return scanlines;
}

png_file_t convert_bmp_file_to_png_file(bitmap_file_t bmp_file)
{
    png_file_t png_file;
    png_file_chunk_t header_chunk;
    png_image_header_chunk_t png_header = convert_bmp_header_to_png_header(bmp_file.info_header);
    scanline_t *scanlines = convert_pixel_array_to_scan_lines(convert_rgb_to_rgba(bmp_file.content,bmp_file.info_header.width, bmp_file.info_header.height), bmp_file.info_header.width, bmp_file.info_header.height);

    png_file.header = png_header;
    png_file.scanlines = scanlines;
    return png_file;
}
