/*
** EPITECH PROJECT, 2024
** bitmap creation
** File description:
** creating a bitmap file
*/

#pragma once
#include <stdlib.h>
#include <unistd.h>

#define MAGIC_WORD "BM"
#define MAGIC_WORD_SIZE 2
#define GET_PADDING(size_x) ((4 - ((size_x * 3) % 4)) % 4)

#define RGB_SIZE 3

typedef struct color_rgb_s {
    char blue;
    char green;
    char red;
} color_rgb_t;


typedef struct bitmap_file_header_s {
    int prog_size;
    int reserved;
    int data_offset;
} bitmap_file_header_t;

typedef struct bitmap_info_header_s {
    // V1 (40 bytes)
    int info_header_size;
    int width;
    int height;
    short plane;
    short bits_per_pixel;
    int compression;
    int image_size;
    int x_pixels_per_meter;
    int y_pixels_per_meter;
    int colors_used;
    int important_colors;

    // v2 (52 bytes)
    int red_mask;
    int green_mask;
    int blue_mask;

    // v3 (56 bytes)
    int alpha_mask;

    //V4 (108 bytes)
    int color_space_type;
    int color_space_endpoints[9];
    int gamma_red;
    int gamma_green;
    int gamma_blue;

    //V5 (124 bytes)
    int intent;
    int profile_data;
    int profile_size;
    int reserved;
} bitmap_info_header_t;

typedef struct bitmap_file_s {
    bitmap_file_header_t file_header;
    bitmap_info_header_t info_header;
    color_rgb_t **content;
}bitmap_file_t;

//generate content

bitmap_file_t generate_blank_bitmap_file(int size_x, int size_y, int info_header_size);

bitmap_file_t get_bitmap_file(char *filename);

color_rgb_t **generate_blank_rgb_content(int size_x, int size_y);

void generate_png_file(void);

void modify_file(color_rgb_t **content, int size_x, int size_y);

void write_bitmap_file(bitmap_file_t file);
