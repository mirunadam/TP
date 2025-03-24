#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LINES 100
#define MAX_LENGTH 30

struct details{
    char name[MAX_LENGTH];
    char artist[MAX_LENGTH];
    int year;
    char combined[MAX_LENGTH];
    bool first;
    bool y2ear;
    bool PlayCount; 
    bool F_G; 
};

int main(int argc, char **argv){
    if(argc != 2){
        printf("ERROR - not enough arguments!\n");
        return EXIT_FAILURE;
    }
    
    FILE *list = fopen(argv[1], "r");
    if(list == NULL){
        printf("File does not exist.\n");
        return EXIT_FAILURE;
    }
    
    struct details line[MAX_LINES];
    int count = 0;
    while(count < MAX_LINES && fscanf(list, "%29[^,],%29[^,],%d,", line[count].name, line[count].artist, &line[count].year) != EOF ){
        printf("%s %s %d\n", line[count].name, line[count].artist, line[count].year);
        count++;
    }
    
    fclose(list);
    return 0;
}
