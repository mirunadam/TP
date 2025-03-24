#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a movie
typedef struct Movie {
    int release_year;
    char title[100];
    double budget;
    struct Movie *next;
} Movie;

// Function to create a new movie node
Movie* createMovie(int release_year, const char *title, double budget) {
    Movie *newMovie = (Movie*)malloc(sizeof(Movie));
    if (newMovie == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newMovie->release_year = release_year;
    strcpy(newMovie->title, title);
    newMovie->budget = budget;
    newMovie->next = NULL;
    return newMovie;
}

// Function to insert a movie into the sorted linked list
void insertMovie(Movie **head, Movie *newMovie) {
    if (*head == NULL || (*head)->release_year > newMovie->release_year ||
        ((*head)->release_year == newMovie->release_year &&
         strcmp((*head)->title, newMovie->title) > 0)) {
        newMovie->next = *head;
        *head = newMovie;
    } else {
        Movie *current = *head;
        while (current->next != NULL &&
               (current->next->release_year < newMovie->release_year ||
                (current->next->release_year == newMovie->release_year &&
                 strcmp(current->next->title, newMovie->title) < 0))) {
            current = current->next;
        }
        newMovie->next = current->next;
        current->next = newMovie;
    }
}

// Function to print the linked list
void printList(Movie *head) {
    printf("Release Year | Title                                | Budget\n");
    printf("------------------------------------------------------------\n");
    while (head != NULL) {
        printf("%13d | %-36s | %.2f\n", head->release_year, head->title, head->budget);
        head = head->next;
    }
}

// Function to free memory allocated for the linked list
void freeList(Movie *head) {
    while (head != NULL) {
        Movie *temp = head;
        head = head->next;
        free(temp);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s movies.csv\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error: Unable to open file.\n");
        return 1;
    }

    char line[256];
    Movie *head = NULL;

    // Skip the first line (header)
    fgets(line, sizeof(line), file);

    // Read movie information from file and insert into linked list
    while (fgets(line, sizeof(line), file)) {
        int release_year;
        char title[100];
        double budget;
        if (sscanf(line, "%d,%99[^,],%lf", &release_year, title, &budget) == 3) {
            Movie *newMovie = createMovie(release_year, title, budget);
            insertMovie(&head, newMovie);
        }
    }

    fclose(file);

    // Print the sorted list
    printList(head);

    // Free memory allocated for the linked list
    freeList(head);

    return 0;
}
