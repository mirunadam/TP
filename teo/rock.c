#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_SONGS 1000

typedef struct {
    char song[256];
    char artist[256];
    int release_year;
} RockSong;

void print_songs_by_year(RockSong songs[], int count, int year) {
    for (int i = 0; i < count; i++) {
        if (songs[i].release_year == year) {
            printf("Song: %s, Artist: %s, Year: %d\n", songs[i].song, songs[i].artist, songs[i].release_year);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <file-path> <year>\n", argv[0]);
        return 1;
    }

    const char *file_path = argv[1];
    int year = atoi(argv[2]);
    RockSong songs[MAX_SONGS];
    int count = 0;

    FILE *file = fopen(file_path, "r");
    if (!file) {
        perror("fopen");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",");
        if (token) {
            strncpy(songs[count].song, token, sizeof(songs[count].song) - 1);
            songs[count].song[sizeof(songs[count].song) - 1] = '\0';
        }

        token = strtok(NULL, ",");
        if (token) {
            strncpy(songs[count].artist, token, sizeof(songs[count].artist) - 1);
            songs[count].artist[sizeof(songs[count].artist) - 1] = '\0';
        }

        token = strtok(NULL, ",");
        if (token) {
            songs[count].release_year = atoi(token);
        }

        count++;
        if (count >= MAX_SONGS) {
            break;
        }
    }

    fclose(file);

    print_songs_by_year(songs, count, year);

    return 0;
}