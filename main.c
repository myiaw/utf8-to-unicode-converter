#include <stdio.h>
#include "pretvori.h"

int main(int argc, char* argv[]) {
    int input = read_args(argv);
    output_character(convert_character(input));
    return 0;
}