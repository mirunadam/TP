#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define SIZE_BUFFER 256
#define SIZE_SONG 30
#define SIZE_ARTIST 45
#define EXAMPLE_SONG 3000


struct rock_songs
{
    char *song;
    char *artist;
    char *realease_year;
};



int main(int argc,char **argv)
{
    FILE *file=fopen(argv[1],"r");
    if(file==NULL)
    {
        perror("File could not be opened");
        exit(EXIT_FAILURE);
    }
    char line[SIZE_BUFFER];
    char *line2;
    char *line3;
    struct rock_songs example_song[EXAMPLE_SONG];    
    int i=0;//index

    fgets(line,sizeof(line),file);
    while(fgets(line,sizeof(line),file))
    {
        if(line[0] == '"')
        {
            example_song[i].song=strtok(line,"\"");
        }
        else
        {

            example_song[i].song=strtok(line,",");
            
        }

         
        example_song[i].artist=strtok(line2,",");

        // char *aux = strtok(line3,",");
        // do
        // {
        //     if(isdigit(aux[0]))
        //     {
        //         // printf("%s \n ",*aux);
        //         example_song[i].realease_year=aux;
        //     }
        
        // }while(!isdigit(aux[0]) && line3!=NULL);
        char *token = strtok(NULL, ",");
        while(token != NULL)
        {
            if(isdigit(*token))
            {
                example_song[i].realease_year = token;
                break;
            }
            token = strtok(NULL, ",");
        }




        
        
        printf("%s | ",example_song[i].song);
        printf("%s | ",example_song[i].artist);
        printf("%s\n",example_song[i].realease_year);
        i++;
    }
    
    fclose(file);
    return 0;
}