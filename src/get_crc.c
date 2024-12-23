/*
** EPITECH PROJECT, 2024
** get_crc
** File description:
** functions to calculate crc values
*/

#define POLYNOMIAL 0x04C11DB7
#define CRC_INPUT_SIZE 8
#include <stdlib.h>

/*Function to create a table for crc values.
These values are used to check for errors in PNG files.

Uses complex math where we caculate 
the polynomial 0x04C11DB7 (x32+x26+x23+x22+x16+x12+x11+x10+x8+x7+x5+x4+x2+x+1)
using xor operations.

Works like a simple euclidian division, But with XOR instead.
Documentation example: http://ross.net/crc/download/crc_v3.txt*/
unsigned int *create_crc_table()
{
    int crc_value;
    unsigned int *crc_table = malloc(256 * sizeof(unsigned int));

    for (int i = 0; i < 256; i++) {
        crc_value = i << 24;
        for (int j = 0; j < CRC_INPUT_SIZE; j++) {
            if (crc_value & 0x80000000) {
                crc_value = (crc_value << 1) ^ POLYNOMIAL;
            } else {
                crc_value <<= 1;
            }
        }
        crc_table[i] = crc_value;
    }
    return crc_table;
}

unsigned int get_crc_value(unsigned int *crc_table, const char *data, unsigned int length)
{
    unsigned int crc_res = 0xFFFFFFFF;
    unsigned char byte;
    unsigned char table_indice;

    for (int i = 0; i < length; i++) {
        byte = data[i];
        table_indice = (crc_res >> 24) ^ byte;
        crc_res = (crc_res << 8) ^ crc_table[table_indice];
    }
    return crc_res ^ 0xFFFFFFFF;
}

int main(void)
{
    unsigned int *table = create_crc_table();

    const char data[] = "1234";
    unsigned int length = sizeof(data) - 1;
    unsigned int crc = get_crc_value(table, data, length);
    printf("CRC-32: 0x%08X\n", crc);
    return 0;
}
