#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_CITIES 10

int numCities;
int adjacencyMatrix[MAX_CITIES][MAX_CITIES];

// Function to read the adjacency matrix from a file
void readAdjacencyMatrix(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error openingggg file");
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d", &numCities);

    for (int i = 0; i < numCities; i++) {
        for (int j = 0; j < numCities; j++) {
            fscanf(file, "%d", &adjacencyMatrix[i][j]);
        }
    }

    fclose(file);
}

// Function to calculate the cost of a given path
int calculatePathCost(int path[], int size) {
    int cost = 0;
    for (int i = 0; i < size - 1; i++) {
        cost += adjacencyMatrix[path[i]][path[i+1]];
    }
    cost += adjacencyMatrix[path[size-1]][path[0]]; // Returning to the starting city
    return cost;
}

// Function to swap two integers
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to find the shortest route using permutation (brute-force)
void findShortestRoute(int* cities, int start, int end, int* minCost, int* bestPath) {
    if (start == end) {
        int cost = calculatePathCost(cities, numCities);
        if (cost < *minCost) {
            *minCost = cost;
            for (int i = 0; i < numCities; i++) {
                bestPath[i] = cities[i];
            }
        }
    } else {
        for (int i = start; i <= end; i++) {
            swap(&cities[start], &cities[i]);
            findShortestRoute(cities, start + 1, end, minCost, bestPath);
            swap(&cities[start], &cities[i]); // Backtrack
        }
    }
}

int main() {
    const char* filename = "cities"; // Replace with your file name
    readAdjacencyMatrix(filename);

    int cities[MAX_CITIES];
    for (int i = 0; i < numCities; i++) {
        cities[i] = i;
    }

    int minCost = INT_MAX;
    int bestPath[MAX_CITIES];

    findShortestRoute(cities, 0, numCities - 1, &minCost, bestPath);

    printf("The shortest route has a cost of %d\n", minCost);
    printf("The best path is: ");
    for (int i = 0; i < numCities; i++) {
        printf("%d ", bestPath[i]);
    }
    printf("%d\n", bestPath[0]); // Returning to the starting city

    return 0;
}
