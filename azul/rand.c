#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 10

// Function to randomly extract elements from an array
void extract_random_elements(int array[], int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        j = rand() % ARRAY_SIZE; // Generate a random index between 0 and ARRAY_SIZE - 1
        printf("%d ", array[j]); // Print the randomly selected element
    }
    printf("\n");
}

void print_factory_displays(int factory_display[][4]) {
    for (int f = 0; f < 5; f++) {
        printf("Factory Display %d:\n", f + 1);
        for (int i = 0; i < 4; i++) {
            printf("Color for element %d: %d\n", i + 1, factory_display[f][i]);
        }
        printf("\n");
    }
}

int main() {
    int array[ARRAY_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    srand(time(NULL)); // Seed the random number generator with the current time

    printf("Randomly selected elements: ");
    extract_random_elements(array, 4); // Extract 4 random elements from the array

    return 0;
}