#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAX_VERTICES 20000
#define MAX_EDGES 20000
#define swap(x, y) (x = x + y, y = x - y, x = x - y)

typedef struct {
    int from;
    int to;
} Edge;

void deleteEdge(Edge edges[], int from, int to, int *numEdges) {
    bool edgeDeleted = false;
    for (int i = 0; i < *numEdges; i++) {
        if ((edges[i].from == from && edges[i].to == to) ||
            (edges[i].from == to && edges[i].to == from)) {
            for (int j = i; j < *numEdges - 1; j++) {
                edges[j] = edges[j + 1];
            }
            (*numEdges)--;
            edgeDeleted = true;
            break;
        }
    }

    if (!edgeDeleted) {
        printf("Edge {%d, %d} not found in graph.\n", from, to);
    }
}

void calculateVertexDegrees(Edge edges[], int numEdges, int vertexDegrees[]) {
    for (int i = 0; i < numEdges; i++) {
        vertexDegrees[edges[i].from - 1]++;
        if (vertexDegrees[edges[i].from - 1] != vertexDegrees[edges[i].to - 1]) {
            vertexDegrees[edges[i].to - 1]++;
        }
    }
}

void sortVerticesByDegree(int vertexDegrees[], int vertexList[], int numVertices) {
    for (int i = numVertices - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (vertexDegrees[vertexList[j] - 1] > vertexDegrees[vertexList[j + 1] - 1]) {
                swap(vertexList[j], vertexList[j + 1]);
            }
        }
    }
}

void printVerticesByDegree(int vertexDegrees[], int vertexList[], int numVertices) {
    printf("Vertices by degree:\n");
    for (int i = 0; i < numVertices; i++) {
        printf("%d: %d\n", vertexList[i], vertexDegrees[vertexList[i] - 1]);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("Usage: %s <input file> <from vertex> <to vertex>\n", argv[0]);
        return 1;
    }

    FILE* inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        printf("Unable to open file: %s\n", argv[1]);
        return 1;
    }

    int numVertices = 0;
    int numEdges = 0;
    Edge edges[MAX_EDGES];

    while (fscanf(inputFile, "%d %d", &edges[numEdges].from, &edges[numEdges].to) == 2) {
        if (numVertices < edges[numEdges].from) {
            numVertices = edges[numEdges].from;
        }
        if (numVertices < edges[numEdges].to) {
            numVertices = edges[numEdges].to;
        }
        numEdges++;
    }

    fclose(inputFile);



    int from = atoi(argv[2]);
    int to = atoi(argv[3]);
    deleteEdge(edges, from, to, &numEdges)  ;

    int vertexDegrees[MAX_VERTICES] = {0};
    calculateVertexDegrees(edges, numEdges, vertexDegrees);

    int vertexList[MAX_VERTICES];
    for (int i = 0; i < numVertices; i++) {
        vertexList[i] = i + 1;
    }

    sortVerticesByDegree(vertexDegrees, vertexList, numVertices);
    printVerticesByDegree(vertexDegrees, vertexList, numVertices);



    return 0;
}