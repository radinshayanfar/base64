#include <stdio.h>
#include <stdlib.h>

char single6bit_to_base64(char c){
    if (c < 26) {
        return c + 'A';
    }
    if (c < 52) {
        return c - 26 + 'a';
    }
    if (c < 62) {
        return c - 52 + '0';
    }
    if (c == 62) {
        return '-';
    }
    return '_';
}

unsigned char *convert3bytes_to_base64(unsigned char* buffer) {
    unsigned char* out = malloc(4 * sizeof(unsigned char));
    unsigned char byte0 = buffer[0] >> 2;
    unsigned char byte1 = ((buffer[0] & 0b11110011) << 4) | (buffer[1] >> 4);
    unsigned char byte2 = ((buffer[1] & 0b11001111) << 2) | (buffer[2] >> 6);
    unsigned char byte3 = buffer[2] & 0b00111111;
    out[0] = single6bit_to_base64(byte0);
    out[1] = single6bit_to_base64(byte1);
    out[2] = single6bit_to_base64(byte2);
    out[3] = single6bit_to_base64(byte3);
    return out;
}

unsigned char *convert_with_padding(unsigned char* buffer, size_t count) {
    for (int i = 0; i < 3 - count; i++) {
        buffer[2 - i] = 0;
    }
    unsigned char* out = convert3bytes_to_base64(buffer);
    for (int i = 0; i < 3 - count; i++) {
        out[3 - i] = '=';
    }
    return out;
}

int main() {
    FILE *fptr = fopen("test.txt", "rb");
    unsigned char *buffer = malloc(3 * sizeof(unsigned char));

    size_t count;
    while (count = fread(buffer, sizeof(unsigned char), 3, fptr)) {
        unsigned char *converted = convert_with_padding(buffer, count);
        // unsigned char *converted = convert3bytes_to_base64(buffer);
        fwrite(converted, sizeof(unsigned char), 4, stdout);
        free(converted);
    }
    printf("\n");

    fclose(fptr);
    return 0;
}