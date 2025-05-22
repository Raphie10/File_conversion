/*
** EPITECH PROJECT, 2025
** write_png_file
** File description:
** functions to write a png file struct into  a file
*/

#include "../include/png.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverse_header_endian(png_image_header_chunk_t *header)
{
    header->width = reverse_endian(header->width);
    header->height = reverse_endian(header->height);
}

void write_chunk(FILE *file, png_file_chunk_t *chunk)
{
    unsigned int crc;
    unsigned int chunk_size = chunk->size;

    printf("written chunk size: %u\n", chunk_size);
    chunk->size = reverse_endian(chunk->size);
    fwrite(chunk, 1, CHUNK_HEADER_SIZE, file);
    fwrite(chunk->data, chunk_size, 1, file);
    crc = reverse_endian(chunk->crc);
    fwrite(&crc, sizeof(int), 1, file);
}

void *get_scanline_data(scanline_t *scanline, png_image_header_chunk_t header)
{
    unsigned int line_size = 1 + header.width * sizeof(color_rgba_t);
    unsigned int size = header.height * line_size;
    
    void *data = malloc(size);

    for (unsigned int i = 0; i < header.height; i++) {
        memcpy(data + i * line_size, &scanline->filter, 1);
        memcpy(data + i * line_size + 1, (scanline[i]).data, sizeof(color_rgba_t) * header.width);
    }
    return data;
}

png_file_chunk_t create_chunk(char chunk_type[4], void *data, unsigned int data_size)
{
    png_file_chunk_t chunk;
    unsigned int *table = create_crc_table();
    int buffer_size = sizeof(chunk.type) + data_size;
    unsigned char *buffer = malloc(buffer_size);
    printf("data_size :%u\n",data_size);

    chunk.size = data_size;
    strncpy(chunk.type, chunk_type, 4);
    chunk.data = malloc(data_size);
    if (data_size > 0) {
        memcpy(chunk.data, data, data_size);
    }
    else {
        chunk.data = NULL;
    }
    memcpy(buffer, chunk.type, sizeof(chunk.type));
    if (data_size > 0) {
        memcpy(buffer + sizeof(chunk.type), data, data_size);
    }
    
    chunk.crc = get_crc_value(table, (const char *)buffer, buffer_size);
    return chunk;
}

void write_png_file(char *filename, png_file_t png_file)
{
    FILE *file = fopen(filename, "wb");
    unsigned char magic_word[] = {137, 80, 78, 71, 13, 10, 26, 10};
    png_file_chunk_t chunk_data;
    png_file_chunk_t chunk_header;
    png_file_chunk_t chunk_end = create_chunk("IEND", NULL, 0);
    void *scanline_data = get_scanline_data(png_file.scanlines, png_file.header);

    chunk_data = create_chunk("IDAT", scanline_data, png_file.header.height * (1 + png_file.header.width * sizeof(color_rgba_t)));
    reverse_header_endian(&png_file.header);
    chunk_header = create_chunk("IHDR", &png_file.header, PNG_HEADER_SIZE);
    fwrite(magic_word, sizeof(magic_word), 1, file);
    write_chunk(file, &chunk_header);
    write_chunk(file, &chunk_data);
    write_chunk(file, &chunk_end);
    fclose(file);
}

