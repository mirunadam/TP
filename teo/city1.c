#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define MAX_CITIES 10

int numCities;
int adjacencyMatrix[MAX_CITIES][MAX_CITIES];
char cityNames[MAX_CITIES][20]; // Assuming each city name is at most 19 characters long

// Function to read the adjacency matrix from a file
void readAdjacencyMatrix(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
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

// Function to initialize city names
void initializeCityNames() {
    strcpy(cityNames[0], "Timișoara");
    strcpy(cityNames[1], "Oradea");
    strcpy(cityNames[2], "Cluj-Napoca");
    strcpy(cityNames[3], "Iași");
    strcpy(cityNames[4], "București");
}

// Function to calculate the cost of a given path
int calculatePathCost(int path[], int size) {
    int cost = 0;
    for (int i = 0; i < size - 1; i++) {
        cost += adjacencyMatrix[path[i]][path[i+1]];
    }
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
    const char* filename = "cities.txt"; // Replace with your file name
    readAdjacencyMatrix(filename);
    initializeCityNames();

    int cities[MAX_CITIES];
    for (int i = 0; i < numCities; i++) {
        cities[i] = i;
    }

    int startingCity;
    printf("Enter the starting city (0 for Timișoara, 1 for Oradea, 2 for Cluj-Napoca, 3 for Iași, 4 for București): ");
    scanf("%d", &startingCity);

    // Move the starting city to the first position
    if (startingCity != 0) {
        swap(&cities[0], &cities[startingCity]);
    }

    int minCost = INT_MAX;
    int bestPath[MAX_CITIES];

    findShortestRoute(cities, 1, numCities - 1, &minCost, bestPath); // Start permutation from index 1

    printf("The shortest route starting from %s has a cost of %d\n", cityNames[startingCity], minCost);
    printf("The best path is: ");
    for (int i = 0; i < numCities; i++) {
        printf("%s ", cityNames[bestPath[i]]);
    }
    printf("\n");

    return 0;
}