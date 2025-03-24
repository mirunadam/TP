#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

struct details{
    char name[30];
    char artist[30];
    char year[30];
    char combined[30];
    bool first;
    bool year;
    bool PlayCount; 
    bool F_G; 
    
}line;


int main(int argc, char **argv){
    FILE *list = fopen(argv[1], "r");
    if(argc != 2){
        printf("ERROR - not enought arguments! \n");
        exit(EXIT_FAILURE);
    }
    if(list == NULL){
        printf("File does not exist. \n");
        exit(EXIT_FAILURE);
    }
    struct details line[100];
    int count=1;
    while(fscanf(list, "%s,%s,%s,%s,%d,%d,", line[count].name, line[count].artist, )){
       //printf("%s \n", name);
        printf("%s %s ", line[count].name, line[count].artist);
        if(line[count].year != NULL){
            printf("%s \n", line[count].year);
        }
        count++;
    }
    fclose(list);
    return 0;
}