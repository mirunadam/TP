#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256
#define MAX_SIZE 1000

typedef struct {
    int x;
    int y;
} Coordinate;

int solveMaze(char **maze, int rows, int cols, Coordinate start, Coordinate end);
int isValidMove(char **maze, int rows, int cols, int x, int y);
void printMaze(char **maze, int rows, int cols, FILE *outputFile);

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    FILE *outputFile = fopen(argv[2], "w");
    if (outputFile == NULL) {
        perror("Error opening output file");
        fclose(inputFile);
        return EXIT_FAILURE;
    }

    char **maze = malloc(MAX_SIZE * sizeof(char *));
    if (maze == NULL) {
        perror("Memory allocation failed");
        fclose(inputFile);
        fclose(outputFile);
        return EXIT_FAILURE;
    }

    int line_count = 0;
    char buffer[BUFFER_SIZE];
    int num_cols = 0;

    while (fgets(buffer, BUFFER_SIZE, inputFile) != NULL) {
        maze[line_count] = malloc(strlen(buffer) + 1);
        if (maze[line_count] == NULL) {
            perror("Memory allocation failed");
            fclose(inputFile);
            fclose(outputFile);
            for (int i = 0; i < line_count; i++) {
                free(maze[i]);
            }
            free(maze);
            return EXIT_FAILURE;
        }
        strcpy(maze[line_count], buffer);
        int current_length = strlen(buffer);
        if (current_length > num_cols)
            num_cols = current_length;
        line_count++;
    }

    // Ensure start and end points are within the maze bounds
    Coordinate start = {-1, -1};
    Coordinate end = {-1, -1};

    for (int i = 0; i < line_count; i++) {
        for (int j = 0; j < num_cols; j++) {
            if (maze[i][j] == 'S') {
                start.x = i;
                start.y = j;
            } else if (maze[i][j] == 'E') {
                end.x = i;
                end.y = j;
            }
        }
    }

    if (start.x == -1 || start.y == -1 || end.x == -1 || end.y == -1) {
        printf("Start or end point not found in the maze.\n");
        fclose(inputFile);
        fclose(outputFile);
        for (int i = 0; i < line_count; i++) {
            free(maze[i]);
        }
        free(maze);
        return EXIT_FAILURE;
    }

    // Ensure start and end points are within the maze bounds
    if (start.x < 0 || start.x >= line_count || start.y < 0 || start.y >= num_cols ||
        end.x < 0 || end.x >= line_count || end.y < 0 || end.y >= num_cols) {
        printf("Start or end point is out of bounds.\n");
        fclose(inputFile);
        fclose(outputFile);
        for (int i = 0; i < line_count; i++) {
            free(maze[i]);
        }
        free(maze);
        return EXIT_FAILURE;
    }

    if (solveMaze(maze, line_count, num_cols, start, end)) {
        printf("Maze solved successfully.\n");
        printMaze(maze, line_count, num_cols, outputFile);
    } else {
        printf("Maze cannot be solved.\n");
    }

    fclose(inputFile);
    fclose(outputFile);
    for (int i = 0; i < line_count; i++) {
        free(maze[i]);
    }
    free(maze);

    return EXIT_SUCCESS;
}


int solveMaze(char **maze, int rows, int cols, Coordinate start, Coordinate end) {
    // Check if start and end coordinates are within the maze bounds
    if (start.x < 0 || start.x >= rows || start.y < 0 || start.y >= cols ||
        end.x < 0 || end.x >= rows || end.y < 0 || end.y >= cols) {
        printf("Invalid start or end coordinates.\n");
        return 0;
    }

    // Implement backtracking algorithm to solve the maze
    if (start.x == end.x && start.y == end.y) {
        return 1; // Maze is solved
    }

    // Mark the current cell as visited
    maze[start.x][start.y] = '.';

    // Try moving in all four directions
    Coordinate nextMove[] = {{start.x + 1, start.y}, {start.x - 1, start.y},
                             {start.x, start.y + 1}, {start.x, start.y - 1}};

    for (int i = 0; i < 4; i++) {
        int nextX = nextMove[i].x;
        int nextY = nextMove[i].y;

        // Check if the next move is within the maze bounds and is a valid move
        if (nextX >= 0 && nextX < rows && nextY >= 0 && nextY < cols &&
            maze[nextX][nextY] != '#' && maze[nextX][nextY] != '.') {
            // Recursively try the next move
            if (solveMaze(maze, rows, cols, nextMove[i], end)) {
                return 1; // Path found
            }
        }
    }

    // No valid path found, unmark the current cell
    maze[start.x][start.y] = ' ';

    return 0; // No path found
}



int isValidMove(char **maze, int rows, int cols, int x, int y) {
    return (x >= 0 && x < rows && y >= 0 && y < cols && maze[x][y] != '#');
}

void printMaze(char **maze, int rows, int cols, FILE *outputFile) {
    if (maze == NULL || outputFile == NULL) {
        printf("Invalid maze or output file.\n");
        return;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(outputFile, "%c", maze[i][j]);
        }
        fprintf(outputFile, "\n");
    }
}
