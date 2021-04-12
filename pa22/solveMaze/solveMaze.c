#include "../graphutils.h" // header for functions to load and free adjacencyList

// A program to solve a maze that may contain cycles using BFS

// BFS requires using a queue data structure
typedef struct QueueNode {
	graphNode_t graphNode;
	struct QueueNode *next;
} QueueNode;

struct Queue {
	struct QueueNode *front; // front (head) of the queue
	struct QueueNode *back; // back (tail) of the queue
};
typedef struct Queue Queue;

// Append a new QueueNode to the back of the Queue
struct Queue enqueue(struct Queue queue, graphNode_t graphNode) {
	/* ... */

	if (queue.front && queue.back) {
		queue.back->next = (QueueNode*) malloc(sizeof(QueueNode));
		queue.back->next->graphNode = graphNode;
		queue.back->next->next = NULL;
		queue.back = queue.back->next;
	} else {
		queue.front = (QueueNode*) malloc(sizeof(QueueNode));
		queue.front->graphNode = graphNode;
		queue.front->next = NULL;
		queue.back = queue.front;
	}

	return queue;
}

// Remove a QueueNode from the front of the Queue
graphNode_t dequeue(Queue *queue) {
	/* ... */
	if (queue->front && queue->back) {
		QueueNode *head = queue->front;

		queue->front = head->next;
		if (head->next == NULL) {
			queue->back = queue->front;
		}

		graphNode_t topNode = head->graphNode;
		free(head);
		return topNode;
	} else {
		//no elements in queue
		return 0;
	}
}


int main(int argc, char *argv[]) {
	// READ INPUT FILE TO CREATE GRAPH ADJACENCY LIST
	AdjacencyListNode *adjacencyList = NULL;
	/* ... */
	size_t graphNodeCount;
	graphNodeCount = adjMatrixToList(argv[1], &adjacencyList);

	// First, read the query file to get the source and target nodes in the maze
	/* ... */
	FILE *fp = fopen(argv[2], "r");
	if (!fp) {
		perror("fopen failed");
		return EXIT_FAILURE;
	}
	graphNode_t sourceNode;
	graphNode_t targetNode;
	fscanf(fp, "%lu", &sourceNode);
	fscanf(fp, "%lu",& targetNode);


	// An array that keeps track of who is the parent node of each graph node we visit
	graphNode_t *parentsOnPath = calloc(graphNodeCount, sizeof(graphNode_t));
	for (size_t i = 0; i < graphNodeCount; ++i) {
		parentsOnPath[i] = -1; // -1 indicates that a nodes is not yet visited
	}

	// USE A QUEUE TO PERFORM BFS
	Queue queue;
	queue.front = queue.back = NULL;

	/* ... */
	parentsOnPath[sourceNode] = targetNode;
	queue = enqueue(queue, sourceNode);
	while (queue.front != NULL) {
		graphNode_t currentNode = dequeue(&queue);
		if (currentNode == targetNode) {
			break;
		}

		AdjacencyListNode *nextNodes = adjacencyList[currentNode].next;
		while (nextNodes != NULL) {
			graphNode_t nextNode = nextNodes->graphNode;

			if (parentsOnPath[nextNode] == -1) {
				//the neighbor has not been reached.
				parentsOnPath[nextNode] = currentNode;
				queue = enqueue(queue, nextNode);

				nextNodes = nextNodes->next;
			} else {
				nextNodes = nextNodes->next;
			}
		}
	}

	// Now that we've found the target graph node, use the parent array to print maze solution
	// Print the sequence of edges that takes us from the source to the target node
	/* ... */
	graphNode_t currNode = targetNode;
	graphNode_t prevNode = parentsOnPath[targetNode];
	while(prevNode != targetNode){
		fprintf(stdout, "%lu", prevNode);
		fprintf(stdout, " %lu\n", currNode);

		currNode = prevNode;
		prevNode = parentsOnPath[prevNode];
	}

	// free any queued graph nodes that we never visited because we already solved the maze
	while (queue.front != NULL) {
		dequeue(&queue);
	}

	free(parentsOnPath);
	freeAdjList(graphNodeCount, adjacencyList);
	fclose(fp);
	return EXIT_SUCCESS;
}
