/*
** EPITECH PROJECT, 2025
** compression
** File description:
** compression file
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../include/compression.h"

void *move_data_left(char *data, int size)
{
    memmove(data, data + 1, size - 1);
    return data;
}

void read_data_from_the_right(char *data, int size)
{
    for (int i = MAX_SLIDING_WINDOW_SIZE - size - 1; i < MAX_SLIDING_WINDOW_SIZE; i++) {
        printf("%c", data[i]);
    }
    printf("\n");
}

void move_data_from_look_ahead_buffer_to_sliding_window(char *sliding_window, char *look_ahead_buffer)
{
    move_data_left(sliding_window, MAX_SLIDING_WINDOW_SIZE);
    sliding_window[MAX_SLIDING_WINDOW_SIZE - 1] = look_ahead_buffer[0];
    move_data_left(look_ahead_buffer, LOOK_AHEAD_BUFFER_SIZE);
}

// void *lzss_compression(unsigned char *data, int size)
// {
//     char *compressed_data = malloc(sizeof(char) * size);
//     char *sliding_window = malloc(sizeof(char) * MAX_SLIDING_WINDOW_SIZE);
//     unsigned char *look_ahead_buffer = malloc(sizeof(char) * LOOK_AHEAD_BUFFER_SIZE);
//     int data_index = 0;
//     int copy_size;

//     if (size < LOOK_AHEAD_BUFFER_SIZE) {
//         copy_size = size;
//     } else {
//         copy_size = LOOK_AHEAD_BUFFER_SIZE;
//     }

//     look_ahead_buffer = memcpy(look_ahead_buffer, data, copy_size);
//     while (data_index + LOOK_AHEAD_BUFFER_SIZE <  size) {
        
//         puts("\nlook_ahead_buffer");
//         write(1, look_ahead_buffer, LOOK_AHEAD_BUFFER_SIZE);
//         // read_data_from_the_right(sliding_window, data_index);
//         move_data_from_look_ahead_buffer_to_sliding_window(sliding_window, look_ahead_buffer);
//         if (data_index + LOOK_AHEAD_BUFFER_SIZE < size) {
//             look_ahead_buffer[LOOK_AHEAD_BUFFER_SIZE - 1] = data[data_index + LOOK_AHEAD_BUFFER_SIZE];
//         }
//         printf("\nsliding_window: ");
//         if (data_index < MAX_SLIDING_WINDOW_SIZE) {
//             read_data_from_the_right(sliding_window, data_index);
//         } else {
//             read_data_from_the_right(sliding_window, MAX_SLIDING_WINDOW_SIZE);
//         }
//         data_index++;
//     }
//     // free(sliding_window);
//     // free(look_ahead_buffer);

//     return NULL;
// }

void advance_data_index(window_t *sliding_window, window_t *look_ahead_buffer, int *data_index, int size)
{
    if (sliding_window->size < MAX_SLIDING_WINDOW_SIZE) {
        (sliding_window->size)++;
    } else {
        (sliding_window->buffer)++;
    }
    (look_ahead_buffer->buffer)++;
    if (*data_index + LOOK_AHEAD_BUFFER_SIZE >= size) {
        (look_ahead_buffer->size)--;
    }
    (*data_index)++;
}

bool compare_buffer_from_pos(window_t match, window_t sliding_window, int pos) {
    for (int j = 0; j < match.size; j++) {
        if (sliding_window.buffer[pos + j] != match.buffer[j])
            return false;
    }
    return true;
}

lzss_value_t my_strstr(window_t match, window_t sliding_window)
{
    lzss_value_t res;

    for (int i = 0; i < sliding_window.size; i++) {
        if (compare_buffer_from_pos(match, sliding_window, i)) {
            res.type = MATCH;
            res.match.length = match.size;
            res.match.offset = sliding_window.size - i;
            return res;
        }
    }
    res.type = LITERAL;
    res.literal = match.buffer[0];
    return res;
}

lzss_value_t get_match(window_t *sliding_window, window_t *look_ahead_buffer)
{
    lzss_value_t match;
    lzss_value_t prev_match;
    window_t match_window = {look_ahead_buffer->buffer, 0};

    match.type = LITERAL;
    match.literal = look_ahead_buffer->buffer[0];
    for (int i = 0; i < sliding_window->size; i++) {
        prev_match = match;
        match_window.size = i;
        match = my_strstr(match_window, *sliding_window);
        if (match.type == LITERAL && prev_match.type == MATCH)
            return prev_match;
    }
    return match;
}

void put_lzss_value(lzss_value_t value)
{
    char res[50];
    if (value.type == LITERAL) {
        sprintf(res, "\nLiteral: %c\n", value.literal);
        write(1, res, strlen(res));
    } else {
        sprintf(res, "\nMatch: offset: %d, length: %d\n", value.match.offset, value.match.length);
        write(1, res, strlen(res));
    }
}

void *lzss_compression(unsigned char *data, int size)
{
    char *compressed_data = malloc(sizeof(char) * size);
    window_t look_ahead_window = {data, 0};
    window_t sliding_window = {data, 0};
    lzss_value_t value;
    int data_index = 0;

    if (size < LOOK_AHEAD_BUFFER_SIZE) {
        look_ahead_window.size = size;
    } else {
        look_ahead_window.size = LOOK_AHEAD_BUFFER_SIZE;
    }
    // advance_data_index(&sliding_window, &data_index, &sliding_window_size, &lookahead_buffer_size, &look_ahead_buffer, &size);
    // write(1, "look_ahead_buffer:", 18);
    // write(1, look_ahead_buffer, lookahead_buffer_size);
    // write(1, "\nsliding_window:", 16);
    // write(1, sliding_window, sliding_window_size);
    while (data_index < size) {
        advance_data_index(&sliding_window, &look_ahead_window, &data_index, size);
        value = get_match(&sliding_window, &look_ahead_window);
        write(1, "\nlook_ahead_buffer:", 19);
        write(1, look_ahead_window.buffer, look_ahead_window.size);
        write(1, "\nsliding_window:", 16);
        write(1, sliding_window.buffer, sliding_window.size);
        put_lzss_value(value);
    }
}

void *data_compression(void *data, int size)
{
    
    return NULL;
}

int main(void)
{
    char *data = "Hello World!";
    char *large_data = "ABCABCABC";
    lzss_compression(large_data, 9);
    // lzss_compression(data, strlen(data));
    // read_data_from_the_right(data, strlen(data));
    return 0;
}