#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    // first, read the number
    signed short int input;
    fscanf(fp, "%hd", &input); // note how the 'h' modifier shortens the %d to half size
     int bin[16];
     int i=0;
    // print bits; you will see this kind of for loop often in this assignment
    for ( int digit=15; 0<=digit; digit-- ) {
        bool char_val = 0b1 & input>>digit; // shift and mask
        bin[i]=char_val;
        i++;

    }

     int s1 = bin[0]*8+bin[1]*4+bin[2]*2+bin[3]*1;
     int s2 = bin[4]*8+bin[5]*4+bin[6]*2+bin[7]*1;
     int s3 = bin[8]*8+bin[9]*4+bin[10]*2+bin[11]*1;
     int s4 = bin[12]*8+bin[13]*4+bin[14]*2+bin[15]*1;
    if(s1>=10){
      s1=65+(s1-10);
    }else{
      s1=s1+48;
    }
    if(s2>=10){
      s2=65+(s2-10);
    }else{
      s2=s2+48;
    }
    if(s3>=10){
      s3=65+(s3-10);
    }else{
      s3=s3+48;
    }
    if(s4>=10){
      s4=65+(s4-10);
    }else{
      s4=s4+48;
    }
      printf("%c%c%c%c\n",s1,s2,s3,s4);


    return EXIT_SUCCESS;

}
