#include <stdio.h>
#include <stdlib.h>
#define MAX 1000

//char maze[MAX][MAX];
char **maze;
int nr_l=0, nr_c=0;


void print(FILE *output){
    for (int i = 0; i < nr_l; i++) {
        for (int j = 0; j < nr_c; j++) {
            fputc(maze[i][j], output);
        }
        //fputc('\n', output);
    }
}

void move(int x, int y, FILE *output){

    if (x < 0 || x >= nr_l || y < 0 || y >= nr_c) {
        return;
    }

    if(maze[x][y] == 'E'){
        maze[x][y]='!';
        print(output);
        printf("CHECKK");
        exit(0);
    }

    if (maze[x][y] != ' ' && maze[x][y] != 'S') {
        return;
    }

    maze[x][y]='.';

    
   // if (maze[x-1][y] == ' ') //move left
    move(x-1, y, output);
   // if (maze[x][y+1] == ' ') //move down
    move(x, y+1, output);
   // if (maze[x+1][y] == ' ') //move right
    move (x+1, y, output);
   // if (maze[x][y-1] == ' ') //move up
    move (x, y-1, output);    

   maze[x][y]=' ';

   
}


int main(int argc, char **argv){
    if(argc != 3){
        perror("ERROR - not enough arguments !!!\n");
        exit(-1);
    }

    FILE *input = fopen(argv[1], "r");
    //FILE *output = fopen(argv[2], "r");

    if(input == NULL){
        perror("ERROR - cannot open file !!!\n");
        exit(-1);
    }

    FILE *output = fopen(argv[2], "a");
    if (output == NULL) {
        printf("ERROR - cannot open file !!!\n");
        exit(-1);
    }

    int i=0;
    int j=0;
    char c;
    int x_start, y_start;
    int x_end, y_end;

   while ((c = fgetc(input)) != EOF) {
        if (c == '\n') {
            nr_l++;
            if (nr_c == 0) {
                nr_c = ftell(input) - (nr_l - 1);
            }
        }
    }

    // Reset file pointer to the beginning of the file
    fseek(input, 0, SEEK_SET);

    maze = (char **)malloc(MAX * sizeof(char *));
    for (int i = 0; i < nr_l; i++){
        maze[i] = (char *)malloc(MAX * sizeof(char));
        if (maze[i] == NULL) {
            printf("Memory allocation failed!\n");
            exit(-1);
        }
    }

    if (maze == NULL) {
        perror("ERROR - memory allocation failed");
        fclose(input);
        fclose(output);
        exit(-1);
    }

    for(i=0; i<nr_l; i++){
        for(j=0; j<nr_c+1; j++){
           
            maze[i][j]=fgetc(input);
            if(maze[i][j] == 'S'){
                x_start=i+1;
                y_start=j+1;
            }
            if(maze[i][j] == 'E'){
                x_end=i+1;
                y_end =j+1;
            }
            //printf("%c", maze[i][j]);
        }
        //printf("\n");
    }

    /*while((c = fgetc(input))!=EOF){
        if(c=='S'){
            x=i;
            y=j;
        }
        maze[i][j]=c;
        i++;
        j++;
    
    }*/
    //printf("\n");
    printf("Nr of lines=%d, nr of cols=%d\n", nr_l, nr_c);
    printf("Start coord x=%d, y=%d\n", x_start, y_start);
    printf("End coord x=%d, y=%d\n", x_end, y_end);
    move(x_start, y_start, output);
    print(output);



    /*for (i = 0; i < nr_l; i++) {
        for (j = 0; j < nr_c; j++) {
            printf("%c", maze[i][j]);
        }
        printf("\n");
    }*/

    for (int i = 0; i < nr_l; i++)
        free(maze[i]);
    free(maze);

    fclose(input);
    fclose(output);
    
    return 0;
}


