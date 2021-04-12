#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {

  FILE* fp = fopen(argv[1], "r");
  if (!fp) {
    perror("fopen failed");
    return EXIT_FAILURE;
  }
  char buff1[256];
  fscanf(fp, "%s", buff1);
   int length1 = atoi(buff1);
  // printf("%d\n",length1);
   char buff2[256];
   fscanf(fp, "%s", buff2);
    int length2 = atoi(buff2);
  //  printf("%d\n",length2);


   int* vector_b = malloc( length1 * sizeof(int*) );
   for ( int i=0; i<length1; i++ ) {
       fscanf(fp, "%s", buff1);
       *(vector_b+i) = atoi(buff1);
      // printf("%ld\n",(long int)(vector_b+i));
     }
       for (int i=0; i<length1; i++) {
        // printf("(vector_b+%d) = %d\n", i, *(vector_b+i));
       }

for(int i=0; i<length1; i++){
       for(int j=0; j<length1-1; j++){
           if(*(vector_b+j) > *(vector_b+j+1)){
               int temp = *(vector_b+j);
              *(vector_b+j) = *(vector_b+j+1);
              *(vector_b+j+1) = temp;

       }
     }
   }
       for(int i=length1-1; i>(length1-length2-1); i--){
       printf(" %d\n", *(vector_b+i));

   }

free(vector_b);
     fclose(fp);

}
