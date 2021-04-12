#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    // SETUP

    // first, read the minuend (number to be subtracted from)
    char buff;
    bool minuend[8]; // suggested that you store bits as array of bools; minuend[0] is the LSB
    for (int i=7; 0<=i; i--) { // read MSB first as that is what comes first in the file
      minuend[i] = (fgetc(fp) == '1');
    }

    // notice that you are reading two different lines; caution with reading
    /* ... */

    while ((buff = fgetc(fp)) != EOF){
        if (buff == '\n'){
            break;
        }
    }


    // second, read the subtrahend (number to subtract)

    bool subtrahend[8]; // suggested that you store bits as array of bools; subtrahend[0] is the LSB
    for (int i=7; 0<=i; i--) { // read MSB first as that is what comes first in the file
          subtrahend[i] = (fgetc(fp) == '1');
    }

    // WE WILL DO SUBTRACTION BY NEGATING THE SUBTRAHEND AND ADD THAT TO THE MINUEND

    // Negate the subtrahend
    // flip all bits
    /* ... */
    for (int i = 0; i < 8; i++){
        subtrahend[i] = !subtrahend[i];
    }

    // add one
    bool carry = true; // to implement the 'add one' logic, we do binary addition logic with carry set to true at the beginning
    for (int i=0; i<8; i++) { // iterate from LSB to MSB
      if (subtrahend[i]){
              subtrahend[i] = false;
      } else{
          subtrahend[i] = carry;
          break;
      }
  }


    // Add the minuend and the negated subtrahend
    bool difference[8]= {0};
    carry = false;
    for (int i = 0; i < 8; i++){ // iterate from LSB to MSB
        if (subtrahend[i]){
            if (minuend[i]){
                difference[i] = carry;
                carry = true;
            }else{
                difference[i] = !carry;
            }
        }
        else{
            if (minuend[i]){
                if (carry){
                    carry = true;
                }
                else{
                    difference[i] = true;
                    carry = false;
                }
            }
            else{
                difference[i] = carry;
                carry = false;
            }
        }
    }

    // print the difference bit string
    for (int i=7; 0<=i; i--)
        printf("%d",difference[i]);

    return EXIT_SUCCESS;

}
