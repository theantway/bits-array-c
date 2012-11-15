#include <stdlib.h>
#include <stdio.h>
#include "bits_array.h"

bits_arr_t bits_arr_init(size_t size) {
    bits_arr_t bits_arr = (bits_arr_t)calloc(1, size);
    return bits_arr;
}

void bits_arr_destory (bits_arr_t bits_arr) {
    free(bits_arr);
    bits_arr = NULL;
}

void bits_arr_set(bits_arr_t bits_arr, size_t pos, int value) {
    int byte_index = pos / 8;
    int byte_offset = pos%8;

    unsigned char* byte = ((unsigned char*)bits_arr) + byte_index;
    unsigned char original_val = *byte;

    unsigned char left_part = (original_val >> (8 - byte_offset - 1) | value) << (8 - byte_offset - 1);

    unsigned char right_part = (original_val << (byte_offset +1) ) >> (byte_offset+1);

    *byte = left_part | right_part;
}

int bits_arr_test(bits_arr_t bits_arr, size_t pos) {
    int byte_index = pos / 8;
    int byte_offset = pos%8;

    unsigned char* byte = ((unsigned char*)bits_arr) + byte_index;
    unsigned char original_val = *byte;

    int result = (original_val >> (8 - byte_offset - 1)) & 1;

    return result > 0;
}

void bits_arr_to_asc(bits_arr_t bits_arr, unsigned char* out, size_t len) {
    unsigned char* byte;
    int bit_index;
    for(byte = bits_arr; byte < bits_arr + len; byte++) {
        unsigned char val = *byte;
        for( bit_index = 7; bit_index >= 0; bit_index--) {
            *(out++) = (val & 0x80) > 0 ? '1': '0';
            val <<= 1;
        }
        *(out++) = ' ';
    } 
    *(out -1) ='\0';
}

void bits_arr_print(bits_arr_t bits_arr, size_t len) {
    unsigned char* buf = (unsigned char*)calloc(1, len * (8 + 1) + 1);

    bits_arr_to_asc(bits_arr, buf, len);
    printf("%s\n", buf);
    free(buf);
}
