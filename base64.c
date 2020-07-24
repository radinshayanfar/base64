#include <stdio.h>

int main() {
    FILE *fptr = fopen("test.txt", "rb");
    unsigned char buffer[3];

    size_t count;
    while ((count = fread(buffer, sizeof(unsigned char), 3, fptr)) == 3)
        printf("%c%c%c\n", buffer[0], buffer[1], buffer[2]);
    if (count != 0) {
        // There are remaining characters. need padding
        fwrite(buffer, sizeof(unsigned char), count, stdout);
        printf("\npadding needed.\n");
    }

    fclose(fptr);
    return 0;
}