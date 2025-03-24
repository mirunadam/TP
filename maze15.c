#include <stdio.h>
#include<stdlib.h>


#define MAX_SIZE 1000

char maze[MAX_SIZE][MAX_SIZE];
int rows=0, cols=0;

int move(int x,int y) {
    if(x<0  || x>=rows || y>cols  ||  y<0 || maze[x][y] == '#' || maze[x][y]=='.')
      return 0;
if(maze[x][y]=='E')
    return 1;
maze[x][y]='.';
// if(maze[x][y-1]==' ' || maze[x][y-1]=='E'){
// }
    if(move(x+1,y) || move(x-1,y) ||  move(x,y+1) || move(x,y-1))
     return 1;


// if(maze[x+1][y]==' ' || maze[x+1][y]=='E') {
//     ;
//     return 1;
// }


// if(maze[x][y+1]==' ' || maze[x][y+1]=='E') {
//    ;
//     return 1;
// }


// if(maze[x-1][y]==' ' || maze[x-1][y]=='E')
// {
//     ;
//     return 1;
// }

maze[x][y]=' ';

return 0;

}



void afisare(FILE *output){
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            fputc(maze[i][j],output);

        }
        fputc('\n',output);
    }
}

int main(int argc,char *argv[]) {
    if (argc!= 3){
        printf("Usage: %s input_file output_file\n",argv[0]);
        return 1;
    }

    FILE *input=fopen(argv[1],"r");
    if (input==NULL) {
        printf("Error opening input file.\n");
        return 1;
    }

    FILE *output=fopen(argv[2],"w");
    if (output==NULL) {
        printf("Error opening output file.\n");
        fclose(input);
        return 1;
    }
char line[MAX_SIZE+1];
int startX=-1,startY=-1;
while(fgets(line,MAX_SIZE,input))
    {
        cols=0;
        while(line[cols]!='\n' && line[cols]!='\0'){
            maze[rows][cols]=line[cols];
        if(maze[rows][cols]=='S') {
                startX=rows;
                startY=cols;
                printf("%d %d",startX,startY);
        }
        cols++;
        }
        rows++;
    }

    move(startX, startY);
    afisare(output);
if(startX==-1 && startY==-1){
printf("Haven�t found the start\n");
fclose(input);
fclose(output);
exit(1);
}
}
