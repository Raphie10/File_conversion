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

typedef struct color_s {
    char blue;
    char green;
    char red;
} color_t;

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
    color_t **content;
}bitmap_file_t;

typedef struct png_file_chunk_s
{
    unsigned int size;
    char type[4];
    void *data;
} png_file_chunk_t;


//generate content

bitmap_file_t generate_blank_file(int size_x, int size_y, int info_header_size);


void print_header(char *filename);

bitmap_file_t get_file(char *filename);
