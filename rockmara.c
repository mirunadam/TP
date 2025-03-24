#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h> // include for error handling
#include <time.h>

#define SIZE_BUFFER 256
#define SIZE_SONG 100
#define SIZE_ARTIST 100
#define EXAMPLE_SONG 3000
#define YEAR_LENGTH 4

struct rock_songs
{
    char song[SIZE_SONG];
    char artist[SIZE_ARTIST];
    char release_year[YEAR_LENGTH + 1]; // +1 for null terminator
};

int sort_songs(const void *a,const void *b)
{
    struct rock_songs *first_song=(struct rock_songs *)a;
    struct rock_songs *second_song=(struct rock_songs *)b;

    if( strcmp(first_song->artist,second_song->artist) > 0){

        return 1;
    }
    else return -1;
}

void bubblesort(struct rock_songs *a, int n)
{
    int i, modified;
    struct rock_songs aux;
    do {
        modified = 0;
        for (i = 1; i < n; i++) {
            if (strcmp(a[i - 1].artist, a[i].artist) > 0) {
                aux = a[i - 1];
                a[i - 1] = a[i];
                a[i] = aux;
                modified = 1;
            }
        }
    } while (modified);
}


int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }



    char lineRead[SIZE_BUFFER];
    struct rock_songs example_song[EXAMPLE_SONG];
    int i = 0; //index

    fgets(lineRead, sizeof(lineRead), file); // Skip the header line

    while (fgets(lineRead, sizeof(lineRead), file) && i < EXAMPLE_SONG)
    {
        char *line = lineRead;
        char *token = strtok(line, ",\"");
        if (token != NULL)
        {
            strcpy(example_song[i].song, token);
            token = strtok(NULL, "\",");
            if (token != NULL)
            {
                strcpy(example_song[i].artist, token);
                token = strtok(NULL, ",");
                while (token != NULL)
                {
                    if (isdigit(*token))
                    {
                        strcpy(example_song[i].release_year, token);
                        break;
                    }
                    else break;//unde nu are an nu il pune
                    token = strtok(NULL, ",");
                }
            }
        }

        printf("%s | %s | %s\n", example_song[i].song, example_song[i].artist, example_song[i].release_year);
        i++;
    }




    fclose(file);
    clock_t start = clock();
    qsort(example_song,i,sizeof(struct rock_songs *),sort_songs);
    //bubblesort(example_song, i);

    clock_t end = 0;
    end = clock();
    double duration = (double)(end - start) / CLOCKS_PER_SEC; //get the time in seconds.
    printf("\n\n\n\n The duration time was %f seconds \n\n\n\n", duration);
    return 0;
}