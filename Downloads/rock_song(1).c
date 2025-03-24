#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include <time.h> //include for the CLOCK function to calculate the runtime

#define SIZE_BUFFER 256
#define SIZE_SONG 30
#define SIZE_ARTIST 45
#define EXAMPLE_SONG 3000
#define YEAR_LENGTH 4

struct rock_songs
{
    char *song;
    char *artist;
    char *realease_year;
};


int main(int argc,char **argv)
{
    clock_t start = clock(); //save the start timestamp
    clock_t end = 0;
    FILE *file=fopen(argv[1],"r");
    if(file==NULL)
    {
        perror("File could not be opened");
        exit(EXIT_FAILURE);
    }
    char *line;
    char lineRead[SIZE_BUFFER];
    struct rock_songs example_song[EXAMPLE_SONG];    
    int i=0;//index

    fgets(lineRead,sizeof(lineRead),file);
    while(fgets(lineRead,sizeof(lineRead),file))
    {
        line = lineRead;
        if(line[0] == '"')
        {
            example_song[i].song=strtok(line,"\"");
            line = strtok(NULL, "\"");
        }
        else
        {

            example_song[i].song=strtok(line,",");
            line = strtok(NULL, ",");
            
        }
        
        example_song[i].artist = strtok(line,",");
        

        while(line != NULL)
        {   
            if(isdigit(*line))
            {
                example_song[i].realease_year = strtok(line,",");
                break;
            }
            line = strtok(NULL, ",");
        }
        
        printf("%s | ",example_song[i].song);
        printf("%s | ",example_song[i].artist);
        printf("%s \n",example_song[i].realease_year);
        i++;
    }
    fclose(file);
    end = clock();
    double duration = (double)(end-start)/CLOCKS_PER_SEC; //get the time in seconds.
    printf("\n\n\n\n The duration time was %f seconds \n\n\n\n",duration);
    return 0;
}