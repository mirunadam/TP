#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_SONG_LENGTH 100
#define MAX_ARTIST_LENGTH 100

typedef struct {
    char song[MAX_SONG_LENGTH];
    char artist[MAX_ARTIST_LENGTH];
    int release_year;
} SongInfo;


int qsort_songs(const void *a,const void *b)
{
    SongInfo *first_song = (SongInfo *)a;
    SongInfo *second_song = (SongInfo *)b;

    return strcmp(first_song->song, second_song->song);

      
}

void bubblesort( SongInfo *a, int n)
{
    int i, modified;
    SongInfo aux;
    do {
        modified = 0;
        for (i = 1; i < n; i++) {
            if (strcmp(a[i - 1].song, a[i].song) > 0) {
                aux = a[i - 1];
                a[i - 1] = a[i];
                a[i] = aux;
                modified = 1;
            }
        }
    } while (modified);
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("ERROR: Incorrect number of arguments.\n");
        printf("Usage: %s <file-path> \n", argv[0]);
        exit(EXIT_FAILURE);
    }

    //int year = atoi(argv[2]);

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("ERROR: Unable to open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    int capacity = 3000;
    int size = 0;
    SongInfo *songs = malloc(capacity * sizeof(SongInfo));
    if (songs == NULL) {
        printf("ERROR: Memory allocation failed\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (size >= capacity) {
            capacity *= 2;
            SongInfo *temp = realloc(songs, capacity * sizeof(SongInfo));
            if (temp == NULL) {
                printf("ERROR: Memory allocation failed\n");
                fclose(file);
                free(songs);
                exit(EXIT_FAILURE);
            }
            songs = temp;
        }

        char *token;
        if (line[0] == '\"') {
            token = strtok(line, "\"");
            strcpy(songs[size].song, token);
            token = strtok(NULL, ",");
        } else {
            token = strtok(line, ",");
            strcpy(songs[size].song, token);
        }

        token = strtok(NULL, ","); //Passing NULL as the first argument tells it to continue tokenizing the same string from its last state.
        strcpy(songs[size].artist, token);

        token = strtok(NULL, ",");

        while(token != NULL){
            if(isdigit( *token)){
                songs[size].release_year = atoi(token);
                break;
            }
            else break;
            token = strtok(NULL, ",");
        }

        size++;
    }
    printf("size: %d\n", size);
    fclose(file);

    clock_t start_bubble = clock();
   
    bubblesort(songs, size);

    clock_t end_bubble = 0;
    end_bubble = clock();
    double duration_bubble = (double)(end_bubble - start_bubble)/ CLOCKS_PER_SEC; //get the time in seconds.
    //printf("\n\n\n\n The duration time for bubblesort was %f seconds \n", duration_bubble);


    clock_t start_q = clock();

    qsort(songs, size, sizeof(SongInfo), qsort_songs);

    clock_t end_q = 0;
    end_q = clock();
    double duration_q = (double)(end_q - start_q)/ CLOCKS_PER_SEC; //get the time in seconds.
    //printf("\n The duration time for qsort was %f seconds \n\n\n\n", duration_q);

    for(int i=0;i<size;i++)
    {
        if (songs[i].release_year == 0) {
            printf("SONG: %s, ARTIST: %s,  release year MISSING\n", songs[i].song, songs[i].artist);
        }
        else{
            printf("SONG: %s, ARTIST: %s,  RELEASE YEAR: %d\n", songs[i].song, songs[i].artist, songs[i].release_year);
        }
    }

    printf("\n\n\n\n The duration time for bubblesort was %f seconds \n", duration_bubble);
    printf("\n The duration time for qsort was %f seconds \n\n\n\n", duration_q);

    free(songs);

    return 0;
}
