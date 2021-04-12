#include "../graphutils.h"

// A program to find a cycle in a directed graph

// You may use DFS or BFS as needed
/* known cycles */
void dfs(bool *isCyclic, AdjacencyListNode *adjacencyList,
		size_t graphNodeCount, graphNode_t source, graphNode_t *parents,
		graphNode_t *path, size_t pathLength) {

	if(*isCyclic){
		return;
	}

	if (parents[source] == -1) {
		parents[source] = source;

		AdjacencyListNode *nextNodes = adjacencyList[source].next;
		while (nextNodes != NULL) {
			graphNode_t nextNode = nextNodes->graphNode;

			path[pathLength] = source;
			dfs(isCyclic, adjacencyList, graphNodeCount, nextNode, parents,
					path, pathLength + 1);
			nextNodes = nextNodes->next;
		}
	} else {
		//already reached. try to find it on path
		size_t startIndex = -1;
		for (size_t i = 0; i < pathLength; i++) {
			if (path[i] == source) {
				startIndex = i;
			}
		}

		if (startIndex != -1) {
			*isCyclic = true;
			for (size_t i = startIndex; i < pathLength; i++) {
				printf("%zu\n ", path[i]);
			}
		}
	}
}

int main(int argc, char *argv[]) {

	// READ INPUT FILE TO CREATE GRAPH ADJACENCY LIST
	AdjacencyListNode *adjacencyList;
	/* ... */
	size_t graphNodeCount;
	graphNodeCount = adjMatrixToList(argv[1], &adjacencyList);

	graphNode_t *parents = calloc(graphNodeCount, sizeof(graphNode_t));
	graphNode_t *path = calloc(graphNodeCount, sizeof(graphNode_t));

	bool isCyclic = false;
	for (unsigned source = 0; source < graphNodeCount; source++) {
		/* ... */
		for (size_t i = 0; i < graphNodeCount; i++) {
			parents[i] = -1; // -1 indicates that a nodes is not yet visited;
		}

		dfs(&isCyclic, adjacencyList, graphNodeCount, source, parents, path, 0);
	}

	free(parents);
	free(path);
	if (!isCyclic) {
		printf("DAG\n");
	}

	freeAdjList(graphNodeCount, adjacencyList);
	return EXIT_SUCCESS;
}
