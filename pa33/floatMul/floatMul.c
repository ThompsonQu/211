#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#define EXP_SZ 8
#define FRAC_SZ 23
#define TOTAL_BITS 32

int main(int argc, char *argv[]) {

    // float value = *(float *) &binary; // you are not allowed to do this.
    // unsigned int binary = *(unsigned int*) &value; // you are not allowed to do this.

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    // SETUP

    // first, read the binary number representation of multiplier
    char buff;
    unsigned int mul1 = 0;
    for (int i = EXP_SZ + FRAC_SZ; 0 <= i; i--){
      mul1 <<= 1;
      mul1 |= ((fgetc(fp) == '1') ? 1 : 0);
    }
    // notice that you are reading two different lines; caution with reading
    while ((buff = fgetc(fp)) != EOF){
        if (buff == '\n'){
            break;
        }
    }
    unsigned int mul2 = 0;
    for (int i = EXP_SZ + FRAC_SZ; 0 <= i; i--){
        mul2 <<= 1;
        mul2 |= ((fgetc(fp) == '1') ? 1 : 0);
    }

    // first, read the binary number representation of multiplcand
    /* ... */

    float product = *(float *) &mul1 * *(float *) &mul2; // you are not allowed to print from this.
    unsigned int ref = *(unsigned int *) &product; // you are not allowed to print from this. But you can use it to validate your solution.

    float val1 = 0.0f;
    float val2 = 0.0f;
    if (mul1 != 0){
        unsigned bin = mul1;
        bool sign = bin & (1 << (EXP_SZ + FRAC_SZ));
        int e = (int)((bin & ((((unsigned int)~0) << (TOTAL_BITS - EXP_SZ)) >> 1)) >> FRAC_SZ) - ((1 << (EXP_SZ - 1)) - 1);
        int mbits = (bin & (((~0) << (1 + EXP_SZ)) >> (1 + EXP_SZ)));
        double m = 1.0;
        for (int i = 0; i < FRAC_SZ; i++){
            if (mbits & 1)  {
                m += pow(0.5, FRAC_SZ - i);
            }
            mbits >>= 1;
        }

        double num = ldexp(m, e);
        num = sign ? -num : num;

        val1 = num;
    }

    if(mul2 != 0)  {
        unsigned bin = mul2;
        bool sign = bin & (1 << (EXP_SZ + FRAC_SZ));
        int e = (int)((bin & ((((unsigned int)~0) << (TOTAL_BITS - EXP_SZ)) >> 1)) >> FRAC_SZ) - ((1 << (EXP_SZ - 1)) - 1);

        int mbits = (bin & (((~0) << (1 + EXP_SZ)) >> (1 + EXP_SZ)));
        double m = 1.0;
        for (int i = 0; i < FRAC_SZ; i++){
            if (mbits & 1)  {
                m += pow(0.5, FRAC_SZ - i);
            }
            mbits >>= 1;
        }

        double num = ldexp(m, e);
        num = sign ? -num : num;

        val2 = num;
    }
    float result = val1 * val2;
    bool sign = result < 0.0f ? 1 : 0;
    /* ... */
    printf("%d_",sign);
    assert (sign == (1&ref>>(EXP_SZ+FRAC_SZ)));

    float fraction = sign ? -result : result;
    signed short trial = (1 << (EXP_SZ - 1)) - 1; // start by assuming largest possible exp (before infinit
      while (fraction / pow(2, trial) < 1.0)  {
        if (trial == -((1 << (EXP_SZ - 1)) - 1)){
          break;
        }
        trial--;

        unsigned short bias = (1 << (EXP_SZ - 1)) - 1;
        signed short exp = trial + bias;
        for ( int i=EXP_SZ-1; 0<=i; i-- ) {
        bool t = 1 & exp >> i;
        printf("%d",t);
        assert (trial == (1 &ref >> (i+FRAC_SZ)));
      }
    printf("_");

    // print frac

    fraction /= pow(2, trial);
    bool frac[FRAC_SZ + 1]; // one extra LSB bit for rounding
    for (int i = FRAC_SZ; 0 <= i; i--){
        frac[i] = false; // frac set to zero to enable partial credit
        if (fraction >= 1.0){
            frac[i] = true;
            fraction -= 1.0;
        }
        fraction *= 2.0;
    }

    if (exp > 0){
        for (int i = FRAC_SZ; 1 <= i; i--){
            frac[i] = frac[i - 1];
        }
    }

    for (int i = FRAC_SZ - 1; 0 <= i; i--){
        bool bits = frac[i + 1]; // skipping the extra LSB bit for rounding
        printf("%d", bits);

    }
}

  return (EXIT_SUCCESS);
}
