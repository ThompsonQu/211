#include "../graphutils.h" // header for functions to load and free adjacencyList

// A program to determine whether an undirected graph is a tree

// A recursive function that returns true if no cycles found
bool isTreeDFS(size_t graphNodeCount, AdjacencyListNode *adjacencyList,
bool *visited, graphNode_t parent, graphNode_t current) {
	if (visited[current] == true)
		return false;

	visited[current] = true;
	// Now iterate through each of the neighboring graph nodes
	AdjacencyListNode *neighbors = adjacencyList[current].next;
	while (neighbors) {
		 graphNode_t neighbor =neighbors->graphNode;
		if (neighbor != parent) {
			if(!isTreeDFS(graphNodeCount, adjacencyList, visited, current,
					neighbor)){
				return false;
			}
		}
		neighbors = neighbors->next;
	}

	// All DFS searches from current node found no cycles, so graph is a tree from this node
	return true;
}

int main(int argc, char *argv[]) {

	// READ INPUT FILE TO CREATE GRAPH ADJACENCY LIST
	AdjacencyListNode *adjacencyList = NULL;
	size_t counter = adjMatrixToList(argv[1], &adjacencyList);
	// Array of boolean variables indicating whether graph node has been visited
	bool *visited = calloc(counter, sizeof(bool));
	bool isTree = isTreeDFS(counter, adjacencyList, visited,(adjacencyList->graphNode), (adjacencyList->graphNode));
	printf(isTree ? "yes" : "no");
	return EXIT_SUCCESS;
	free(visited);
}
