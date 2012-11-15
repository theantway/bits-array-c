#ifndef BITS_ARRAY_H
#define BITS_ARRAY_H
#include <stdlib.h>

typedef unsigned char* bits_arr_t;

#ifdef __cplusplus
extern "C" {
#endif

bits_arr_t bits_arr_init(size_t size);
void bits_arr_destory (bits_arr_t bits_arr);

void bits_arr_set(bits_arr_t bits_arr, size_t pos, int value);
int bits_arr_test(bits_arr_t bits_arr, size_t pos);

void bits_arr_to_asc(bits_arr_t bits_arr, unsigned char* out, size_t len);
void bits_arr_print(bits_arr_t bits_arr, size_t len);

#ifdef __cplusplus
}
#endif

#endif