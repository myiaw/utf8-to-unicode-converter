#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int read_args(char *cmd[]) {
    return strtol(cmd[1], NULL, 16); //string to long int.
}

// 0x3F is 00111111 in binary
// 0x0F is 00001111 in binary

int convert_character(int unicode_character) {
    if (unicode_character < 0x80 && unicode_character >= 0x00) { // 1 byte --> 0x7F is 01111111 in binary, 0 - 127
        return unicode_character & 0x7F; // This has no use?
    } else if (unicode_character < 0x800 && unicode_character > 0x7F) { // 128 - 2047
        int byte1 = 0xC0; // 110x xxxx --> 11000000
        int byte2 = 0x80; // 10xx xxxx --> 10000000
        int byte1_res = (unicode_character >> 6) | byte1; //Shift unwanted bits to the right and combine with byte1
        int byte2_res = (unicode_character & 0x3F) | byte2; // 0x3F is 0 everywhere except the last 6 bits which are 1, we do or to keep 10 and add the rest.
        return (byte2_res | (byte1_res << 8)); // We shift byte 1 in the beginning and add byte 2 to the end.

    } else if (unicode_character < 0xFFFE && unicode_character > 0x7FF) { // 2048 - 65535
        int byte1 = 0xE0; // 1110 xxxx --> 11100000
        int byte2 = 0x80; // 10xx xxxx --> 10000000
        int byte3 = 0x80; // 10xx xxxx --> 10000000
        int byte1_res = ((unicode_character >> 12) & 0x0F) | byte1; // //Shift unwanted bits to the right and combine with byte1. 0x0F is 00001111 in binary
        int byte2_res = ((unicode_character >> 6) & 0x3F) | byte2; // Combine with middle and push to the right what we don't need -> we leave 10 alone because it has to stay that way.
        int byte3_res = (unicode_character & 0x3F) | byte3; // 0x3F is 00111111 in binary
        return (byte3_res | (byte2_res << 8) | (byte1_res << 16));
    }
    perror("Error: Unicode character is out of range.");
    exit(1);
}

void output_character(int n) {

    int bits = 0;
    long int temp = n;
    while (1) {
        temp >>= 1; // Shift bits to the right till we get to the end.
        bits++;
        if (temp == 0) break;
    }
    int count = 0;

    printf("\n%s", "UTF-8 binarno: ");

    for (int i = bits - 1; i >= 0; i--) {
        if ((n >> i) & 1) {
            printf("%s", "1");
            count += 1;
        } else {
            printf("%s", "0");
            count += 1;
        }
        if (count == 4) {
            printf("%s", " ");
            count = 0;
        }
    }

    printf("\nUTF-8 hex: %X\n", n);
}

