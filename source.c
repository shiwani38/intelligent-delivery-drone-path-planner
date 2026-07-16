#include <stdio.h>
#include <stdbool.h>

#define INFINITY 9999
#define MAX_VERTICES 10

// Function prototypes
void dijkstra(int costMatrix[MAX_VERTICES][MAX_VERTICES], int totalVertices, int sourceVertex);
void printPath(int predecessor[], int currentVertex);

int main() {
    int graph[MAX_VERTICES][MAX_VERTICES];
    int i, j, vertices, source;

    printf("Enter the number of vertices (Max %d): ", MAX_VERTICES);
    if (scanf("%d", &vertices) != 1 || vertices <= 0 || vertices > MAX_VERTICES) {
        printf("Invalid number of vertices.\n");
        return 1;
    }

    printf("\nEnter the adjacency matrix (Use 0 for self-loops and 0 if no direct edge exists):\n");
    for (i = 0; i < vertices; i++) {
        for (j = 0; j < vertices; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("\nEnter the starting source vertex (0 to %d): ", vertices - 1);
    if (scanf("%d", &source) != 1 || source < 0 || source >= vertices) {
        printf("Invalid source vertex.\n");
        return 1;
    }

    dijkstra(graph, vertices, source);

    return 0;
}

void dijkstra(int costMatrix[MAX_VERTICES][MAX_VERTICES], int totalVertices, int sourceVertex) {
    int adjustedCost[MAX_VERTICES][MAX_VERTICES];
    int distance[MAX_VERTICES];
    int predecessor[MAX_VERTICES];
    bool visited[MAX_VERTICES];
    int count, minDistance, nextNode, i, j;
  for (i = 0; i < totalVertices; i++) {
        for (j = 0; j < totalVertices; j++) {
            if (i == j) {
                adjustedCost[i][j] = 0;
            } else if (costMatrix[i][j] == 0) {
                adjustedCost[i][j] = INFINITY;
            } else {
                adjustedCost[i][j] = costMatrix[i][j];
            }
        }
    }

    // Initialize trackers tracking distance, predecessors, and visited logs
    for (i = 0; i < totalVertices; i++) {
        distance[i] = adjustedCost[sourceVertex][i];
        predecessor[i] = sourceVertex;
        visited[i] = false;
    }

    distance[sourceVertex] = 0;
    visited[sourceVertex] = true;
    count = 1;

    while (count < totalVertices - 1) {
        minDistance = INFINITY;
        nextNode = -1;

        // Pick the unvisited node with the minimum absolute distance value
        for (i = 0; i < totalVertices; i++) {
            if (!visited[i] && distance[i] < minDistance) {
                minDistance = distance[i];
                nextNode = i;
            }
        }

        // Prevent loops if remaining nodes are completely unreachable
        if (nextNode == -1) {
            break;
        }

        visited[nextNode] = true;

        // Relaxation step: update cost paths going through the chosen intermediary node
        for (i = 0; i < totalVertices; i++) {
            if (!visited[i]) {
                if (minDistance + adjustedCost[nextNode][i] < distance[i]) {
                    distance[i] = minDistance + adjustedCost[nextNode][i];
                    predecessor[i] = nextNode;
                }
            }
    }
        count++;
    }

    // Print calculated outcomes outlining sequence and accumulated weight totals
    printf("\n=================== RESULT ===================\n");
    printf("Destination\tCost\tShortest Path Sequence\n");
    for (i = 0; i < totalVertices; i++) {
        if (i != sourceVertex) {
            printf("%d\t\t", i);
            if (distance[i] >= INFINITY) {
                printf("INF\tNo reachable path exists");
            } else {
                printf("%d\t%d", distance[i], sourceVertex);
                printPath(predecessor, i);
            }
            printf("\n");
        }
    }
}

// Recursive helper function to reverse-trace structural path sequences
void printPath(int predecessor[], int currentVertex) {
    if (predecessor[currentVertex] == currentVertex) {
        return;
    }
    printPath(predecessor, predecessor[currentVertex]);
    printf(" -> %d", currentVertex);
}
