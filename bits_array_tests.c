#include "bits_array.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void verify_string_repr(const char* expected, bits_arr_t bits_arr, size_t len) {
    char* buf = (char*)calloc(1, len * (8 + 1));
    bits_arr_to_asc(bits_arr, (unsigned char*)buf, len);
    int result = strcmp(expected, buf);
    if( result != 0) {
        printf("%d Expected: %s, but got: %s\n", result, expected, buf);
    }

    free(buf);    
}

void test_bits_arr_to_asc(){
    printf("Testing bits_arr to asc...");
    unsigned char s = 0x80;
    verify_string_repr("10000000", &s, 1);
    printf("OK\n");
}

void test_short_bits_arr(){
    printf("Testing bits_arr set/test and asc representation...");
    int size = 2;

    bits_arr_t bits_arr = bits_arr_init(size);
    assert(bits_arr_test(bits_arr, 0) == 0);
    verify_string_repr("00000000 00000000", bits_arr, size);

    bits_arr_set(bits_arr, 0, 1);
    assert(bits_arr_test(bits_arr, 0) == 1);
    verify_string_repr("10000000 00000000", bits_arr, size);

    bits_arr_set(bits_arr, 7, 1);
    assert(bits_arr_test(bits_arr, 7) == 1);
    verify_string_repr("10000001 00000000", bits_arr, size);

    bits_arr_set(bits_arr, 8, 1);
    assert(bits_arr_test(bits_arr, 8) == 1);
    verify_string_repr("10000001 10000000", bits_arr, size);

    bits_arr_set(bits_arr, 15, 1);
    assert(bits_arr_test(bits_arr, 15) == 1);
    verify_string_repr("10000001 10000001", bits_arr, size);

    bits_arr_destory(bits_arr);
    printf("OK\n");
}

void test_big_bits_arr_performance(){
    printf("Testing big bits_arr set/test performance...");
    int size = 200000000;

    bits_arr_t bits_arr = bits_arr_init(size);
    assert(bits_arr_test(bits_arr, 0) == 0);
    
    bits_arr_set(bits_arr, 0, 1);
    assert(bits_arr_test(bits_arr, 0) == 1);
    
    bits_arr_set(bits_arr, 7, 1);
    assert(bits_arr_test(bits_arr, 7) == 1);
    
    bits_arr_set(bits_arr, 8, 1);
    assert(bits_arr_test(bits_arr, 8) == 1);
    
    bits_arr_set(bits_arr, 15, 1);
    assert(bits_arr_test(bits_arr, 15) == 1);
    
    int pos;
    for(pos =16; pos < size; pos++) {
        assert(bits_arr_test(bits_arr, pos) == 0);    
    }
    bits_arr_destory(bits_arr);
    printf("OK\n");
}

int main(){
    test_bits_arr_to_asc();
    test_short_bits_arr();
    test_big_bits_arr_performance();

    return 0;
}
