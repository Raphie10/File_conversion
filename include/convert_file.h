/*
** EPITECH PROJECT, 2025
** convert file
** File description:
** convert file header
*/

#pragma once
#include "png.h"
#include "bitmap.h"

png_file_t convert_bmp_file_to_png_file(bitmap_file_t bmp_file);

scanline_t *convert_pixel_array_to_scan_lines(color_rgba_t **content, int width, int height);

