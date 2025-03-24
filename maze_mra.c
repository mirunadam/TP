#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000

char **maze;
int nr_l = 0, nr_c = 0;


void print(FILE *output) {
    for (int i = 0; i < nr_l; i++) {
        for (int j = 0; j < nr_c; j++) {
            fputc(maze[i][j], output);
        }
        //fputc('\n', output);
    }
}

void move(int x, int y, FILE *output) {
    if (x < 0 || x >= nr_l || y < 0 || y >= nr_c) {
        return;
    }

    if (maze[x][y] == 'E') {
        maze[x][y]='!';
        print(output);
        exit(0);
    }

    if (maze[x][y] != ' ' && maze[x][y] != 'S') {
        return;
    }

    maze[x][y] = '.';

    move(x - 1, y, output); //move left
    move(x, y + 1, output); //move down
    move(x + 1, y, output); //move right
    move(x, y - 1, output); //move up

    maze[x][y] = ' ';
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        perror("ERROR - not enough arguments !!!\n");
        exit(-1);
    }

    FILE *input = fopen(argv[1], "r");

    if (input == NULL) {
        perror("ERROR - cannot open file !!!\n");
        exit(-1);
    }

    FILE *output = fopen(argv[2], "w");

    if (output == NULL) {
        printf("ERROR - cannot open file !!!\n");
        exit(-1);
    }

    char c;
    while ((c = fgetc(input)) != EOF) {
        if (c == '\n') {
            nr_l++;
            if (nr_c == 0) {
                nr_c = ftell(input) - (nr_l - 1); //ftell returns the current value of the position
            }
        }
    }

    fseek(input, 0, SEEK_SET);

    maze = (char **)malloc(nr_l * sizeof(char *));
    if (maze == NULL) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < nr_l; i++) {
        maze[i] = (char *)malloc(nr_c * sizeof(char));
        if (maze[i] == NULL) {
            printf("Memory allocation failed!\n");
            exit(EXIT_FAILURE);
        }
    }

    int x_start, y_start;
    int x_end, y_end;
    
    for (int i = 0; i < nr_l; i++) {
        for (int j = 0; j < nr_c; j++) {
            maze[i][j]=fgetc(input);
            if (maze[i][j] == 'S') {
                x_start = i;
                y_start = j;
            } else if (maze[i][j] == 'E') {
                x_end = i;
                y_end = j;
            }
        }
    }

    printf("Nr of lines=%d\n", nr_l+1); 
    printf("Nr of cols=%d\n", nr_c-1);
    printf("Start coord x=%d, y=%d\n", x_start+1, y_start+1);
    printf("End coord x=%d, y=%d\n", x_end+1, y_end+1);

    move(x_start, y_start, output);

    fclose(input);
    fclose(output);

    return 0;
}