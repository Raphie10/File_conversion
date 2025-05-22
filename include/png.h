/*
** EPITECH PROJECT, 2025
** png
** File description:
** png header file
*/

#ifndef PNG_H_
#define PNG_H_


typedef struct png_file_chunk_s
{
    unsigned int size;
    char type[4];
    void *data;
    unsigned int crc;
} png_file_chunk_t;

#define POLYNOMIAL 0xEDB88320
#define CRC_INPUT_SIZE 8

typedef struct color_rgba_s {
    char blue;
    char green;
    char red;
    char alpha;
} color_rgba_t;

#define PNG_HEADER_SIZE 13
typedef struct png_image_header_chunk_s
{
    unsigned int width;
    unsigned int height;
    char bit_depth;
    char color_type;
    char compression_method;
    char filter_method;
    char interlace_method;
}png_image_header_chunk_t;


typedef struct scanline_s
{
    char filter;
    color_rgba_t *data;
}scanline_t;

#define CHUNK_HEADER_SIZE sizeof(int) + sizeof(char [4])

typedef struct png_file_s
{
    png_image_header_chunk_t header;
    scanline_t *scanlines;

} png_file_t;


void write_png_file(char *filename, png_file_t png_file);

unsigned int get_crc_value(const unsigned int *crc_table, const unsigned char *data, unsigned int length);

unsigned int *create_crc_table();

unsigned int reverse_endian(unsigned int crc);

#endif /* !PNG_H_ */
