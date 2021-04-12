#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>


typedef struct element {
    char close;
    struct element* next;
} element ;

void push( element** head, int close){
  element* new= malloc(sizeof(element));
    if (new == NULL) {
      return ;
    }
    new->close = close;
    new->next = (*head);
    (*head) = new;
}

char pop( element** headAdd){
  char temp;
  element* head = *headAdd;
  if (head == NULL) {
    return 0;
  }
    temp = head->close;
    *headAdd = head->next;
    free(head);
    return temp;
}

bool match(char c1, char c2){
  if ((c1 == '(' && c2 == ')')||(c1 == '{' && c2 == '}')||(c1 == '[' && c2 == ']')||(c1 == '<' && c2 == '>')){
    return 1;
  }else{
    return 0;
  }
}
int main(int argc, char* argv[]){
    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }
    int balanced = 1;
    char buff;
    element* new = NULL;
    while ( fscanf(fp, "%c", &buff)==1 ) {
      if (buff == '{' || buff == '(' || buff == '['||buff == '<'){
        push(&new, buff);
      }
      if (buff == '}' || buff == ')'|| buff== ']'||buff == '>') {
        if (new == NULL){
         balanced=0;
       }
       if (match(pop(&new), buff)==0){
         balanced =0;
      }
    }
  }
  if (new == NULL){
    balanced= 1;
  }else{
      balanced= 0;
    }
    if(balanced==1){
      printf("yes" );
    }else if (balanced == 0){
      printf("no");
    }

    fclose(fp);
   free(new);
}
