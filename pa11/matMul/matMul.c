#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>



int main(int argc, char* argv[])
{

    FILE* matrix_a_fp = fopen(argv[1], "r");
    if (!matrix_a_fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }
    int buff=0;
    fscanf(matrix_a_fp, "%d", &buff);
    int length_hang = buff;
  //  printf("length_hang %d\n",length_hang);


    int buff4=0;
    fscanf(matrix_a_fp, "%d", &buff4);
    int length_lie = buff4;
  //  printf("length_lie %d\n",length_lie);
    int buff2=0;
  int a[length_hang][length_lie];
  int i=0;
  int j=0;
    while ( fscanf(matrix_a_fp, "%d", &buff2)!=EOF ) {
          //printf("arr %d\n",buff2);
           a[i][j]=buff2;
           j++;
           if(j==length_lie){
             i++;
             j=0;
           }
    }
  fclose(matrix_a_fp);


    FILE* matrix_b_fp = fopen(argv[2], "r");
    if (!matrix_b_fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }
    int buff1=0;
    fscanf(matrix_b_fp, "%d", &buff1);
    int length_hang1 = buff1;
    //printf("length_hang1%d\n",length_hang1);

    int buff5=0;
    fscanf(matrix_b_fp, "%d", &buff5);
    int length_lie1 = buff5;
  // printf("length_lie1%d\n",length_lie1);

    int b[length_hang1][length_lie1];
    int buff3=0;
    int i1=0;
    int j1=0;
      while ( fscanf(matrix_b_fp, "%d", &buff3)!=EOF ) {
             b[i1][j1]=buff3;
             j1++;
             if(j1==length_lie1){
               i1++;
               j1=0;
             }
      }
      for(i=0;i<length_hang1;i++){
        for(j=0;j<length_lie1;j++){
        //  printf("barr %d\n",b[i][j]);
        }
      }

  fclose(matrix_b_fp);

   int c[length_hang][length_lie1];
    int temp;
        for (int i = 0; i < length_hang; i++){
            for (int j = 0; j < length_lie1; j++){
              temp = 0;
                for (int k = 0; k < length_lie; k++){
                    temp += a[i][k] * b[k][j];
                }
                c[i][j] = temp;
            }
        }
    for (i = 0; i<length_hang; i++)
            {
                for (j = 0; j<length_lie1; j++)
                    printf("%d ", c[i][j]);
            }
    return 0;

}
