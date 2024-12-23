/*
** EPITECH PROJECT, 2024
** generate_content
** File description:
** file to generate content with the aim to generate bmp file
*/
#include "../include/bitmap.h"
int get_data_size(int size_x, int size_y)
{
    return (size_x * 3 + GET_PADDING(size_x)) * size_y;
}

int get_prog_size(int size_x, int size_y, int info_header_size)
{
    int prog_size = 0;

    prog_size += MAGIC_WORD_SIZE;
    prog_size += sizeof(bitmap_file_header_t);
    prog_size += info_header_size;
    prog_size += get_data_size(size_x, size_y);
    return prog_size;
}

bitmap_file_header_t create_file_header(int size_x, int size_y, int info_header_size)
{
    bitmap_file_header_t header;

    header.prog_size = get_prog_size(size_x, size_y, info_header_size);
    header.reserved = 0;
    header.data_offset = MAGIC_WORD_SIZE + sizeof(bitmap_file_header_t) + info_header_size;
    return header;
}

bitmap_info_header_t create_info_header(int size_x, int size_y, int info_header_size)
{
    bitmap_info_header_t info_header;

    info_header.info_header_size = info_header_size;
    info_header.width = size_x;
    info_header.height = size_y;
    info_header.plane = 1;
    info_header.bits_per_pixel = 24;
    info_header.compression = 0;
    info_header.image_size = get_data_size(size_x, size_y);;
    info_header.x_pixels_per_meter = 0;
    info_header.y_pixels_per_meter = 0;
    info_header.colors_used = 0;
    info_header.important_colors = 0;
    switch (info_header_size)
    {
    case 52:
        info_header.red_mask = 0x00FF0000;
        info_header.green_mask = 0x0000FF00;
        info_header.blue_mask = 0x000000FF;
    case 56:
        info_header.alpha_mask = 0xFF000000;
    case 108:
    

    
    default:
        break;
    }
    return info_header;
}

color_t **generate_blank_content(int size_x, int size_y)
{
    color_t **content = malloc(sizeof(color_t *) * (size_y + 1));
    color_t *line;

    for (int i = 0; i <= size_y; i++) {
        line = malloc(sizeof(color_t) * (size_x + 1));
        for (int j = 0; j <= size_x; j++) {
            line[j].blue = 255;
            line[j].green = 255;
            line[j].red = 255;
        }
        content[i] = line;
    }
    return content;
}

bitmap_file_t generate_blank_file(int size_x, int size_y, int info_header_size)
{
    bitmap_file_header_t file_header = create_file_header(size_x, size_y, info_header_size);
    bitmap_info_header_t info_header = create_info_header(size_x, size_y, info_header_size);
    color_t **file_content = generate_blank_content(size_x, size_y);
    bitmap_file_t file = {file_header, info_header, file_content};

    return file;
}
