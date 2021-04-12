#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define EXP_SZ 8
#define FRAC_SZ 23
#define TOTAL_BITS 32
int main(int argc, char *argv[]) {

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    // SETUP

    // first, read the binary number representation of float point number
    unsigned int binary = 0;
    for (int i=EXP_SZ+FRAC_SZ; 0<=i; i--) { // read MSB first as that is what comes first in the file
      binary <<= 1;
      binary |= ((fgetc(fp) == '1') ? 1 : 0);
    }
      printf("\n");

    // float number = *(float *)&binary; // you are not allowed to do this.
    bool sign = binary & (1 << (EXP_SZ + FRAC_SZ));

    int e = (int)((binary & ((((unsigned int)~0) << (TOTAL_BITS - EXP_SZ)) >> 1)) >> FRAC_SZ) - ((1 << (EXP_SZ - 1)) - 1);

    // M
    /* ... */
    int mbits = (binary & (((~0) << (1 + EXP_SZ)) >> (1 + EXP_SZ)));
    double m = 1.0;
    for (int i = 0; i < FRAC_SZ; i++){
        if (mbits & 1)
        {
            m += pow(0.5, FRAC_SZ - i);
        }
        mbits >>= 1;
    }
    // https://www.tutorialspoint.com/c_standard_library/c_function_ldexp.htm
    double number = ldexp ( m, e );
    number = sign ? -number : number;
    printf("%e\n", number);

    return EXIT_SUCCESS;

}
