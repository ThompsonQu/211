#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct bstNode bstNode;
struct bstNode {
    int val;
    struct bstNode* l_child;
    struct bstNode* r_child;
};
bstNode* insert ( bstNode* root, int value ) {
    if (root==NULL) {
        root = malloc(sizeof(bstNode));
        root->l_child = NULL;
        root->r_child = NULL;
        root->val = value;
      }
      if(value<root->val){
        root->l_child = insert(root->l_child,value);
      }else if(value==root->val){
           }else {
             root->r_child = insert(root->r_child,value);
             }
             return root;
             free(root);
}
void reverse(bstNode* root){
    if (root == NULL){
          return;
        }
    reverse(root->r_child);
    printf("%d ", root->val);
    reverse(root->l_child);
}


int main(int argc, char* argv[])
{
    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

  struct bstNode* root = NULL;

    int buff=0;
    while ( fscanf(fp, "%d", &buff)!=EOF ) {
      root = insert(root,buff);
    //  printf("%d",buff);
    }
    if(root==NULL){
      //  printf("%d",3);
    }
    reverse(root);

    fclose(fp);
  
    return 0;
}
