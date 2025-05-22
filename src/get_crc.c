/*
** EPITECH PROJECT, 2024
** get_crc
** File description:
** functions to calculate crc values
*/

#include <stdlib.h>
#include "../include/png.h"

unsigned int reverse_endian(unsigned int crc)
{
    return ((crc >> 24) & 0xFF) |
        ((crc >> 8) & 0xFF00) |
        ((crc << 8) & 0xFF0000) |
        ((crc << 24) & 0xFF000000);
}

/*Function to create a table for crc values.
These values are used to check for errors in PNG files.

Uses complex math where we caculate 
the polynomial 0x04C11DB7
(x^32+x^26+x^23+x^22+x^16+x^12+x^11+x^10+x^8+x^7+x^5+x^4+x^2+x+1)
using xor operations.

Works like a simple euclidian division, But with XOR instead.
Documentation example: http://ross.net/crc/download/crc_v3.txt
*/
unsigned int *create_crc_table(void)
{
    unsigned int crc_value;
    unsigned int *crc_table = malloc(256 * sizeof(unsigned int));

    for (int i = 0; i < 256; i++) {
        crc_value = i;
        for (int j = 0; j < CRC_INPUT_SIZE; j++) {
            if (crc_value & 1) {
                crc_value = (crc_value >> 1) ^ POLYNOMIAL;
            } else {
                crc_value >>= 1;
            }
        }
        crc_table[i] = crc_value;
    }
    return crc_table;
}

unsigned int get_crc_value(const unsigned int *crc_table, const unsigned char *data, unsigned int length)
{
    unsigned int crc_res = 0xFFFFFFFF;
    unsigned char byte;
    unsigned char table_indice;

    for (unsigned int i = 0; i < length; i++) {
        byte = data[i];
        table_indice = (crc_res ^ byte) & 0xFF;
        crc_res = (crc_res >> 8) ^ crc_table[table_indice];
    }
    return crc_res ^ 0xFFFFFFFF;
}

void *deflate_data(void *data, unsigned int size)
{
    void *deflated_data = malloc(size);
    unsigned int deflated_size = 0;

    return data;
}
