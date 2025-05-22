/*
** EPITECH PROJECT, 2025
** compression
** File description:
** compression header file
*/
#pragma once

#define MAX_SLIDING_WINDOW_SIZE 32768
#define LOOK_AHEAD_BUFFER_SIZE 258

enum {
    LITERAL,
    MATCH
};

typedef struct lzss_value_s {
    char type;
    union {
        struct match_s {
            short offset;
            char length;
        } match;
        char literal;
    };
} lzss_value_t;

typedef struct window_s {
    char *buffer;
    int size;
} window_t;
