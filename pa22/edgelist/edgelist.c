#include "../graphutils.h" // header for functions to load and free adjacencyList

// A program to print the edge list of a graph given the adjacency matrix
int main ( int argc, char* argv[] ) {

    // FIRST, READ THE ADJACENCY MATRIX FILE
    AdjacencyListNode* adjacencyList = NULL;
    size_t counter=adjMatrixToList(argv[1],&adjacencyList);
    //printf("counter : %ld\n",counter);


    // NEXT, TRAVERSE THE ADJACENCY LIST AND PRINT EACH EDGE, REPRESENTED AS A PAIR OF NODES
    // Example of traversing the adjacency list is in the freeAdjList() function in graphutils.h
    /* ... */
    for (size_t i=0; i<counter; i++) {
      AdjacencyListNode* tar = adjacencyList[i].next;
        while (tar) {
          AdjacencyListNode* now = tar;
          printf("%ld %ld\n", i,now->graphNode);
            tar = tar->next;
            free(now);
        }
      }
      free(adjacencyList);
}
    // NOW, BE SURE TO FREE THE ADJACENCY LIST
    /* ... */
