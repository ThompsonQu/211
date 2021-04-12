#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//Function declerations
int is_prime(int n);

int main(int argc, char* argv[]) {
  int number = atoi(argv[1]);
  int q,w,e;
  if (number < 5){
    return false;
  }
  if(number%2==0){
    return false;
  }
  for (int a = 2; a<number;a++){
    for (int b = 2; b<number;b++){
      for(int c = 2; c<number;c++){
        if(is_prime(a)==1){
          if(is_prime(b)==1){
            if(is_prime(c)==1){
          if (a+b+c==number){
             q=a;
             w=b;
             e=c;
          }
        }
      }
        }
      }
  }
}
 printf("%d = %d + %d + %d", number,q,w,e);
}

int is_prime(int n){
    if (n<2)
      return 0;

    for (int i=2; i<n; i++){
      if ((n%i)==0)
        return 0;
}
    return  1;
}
