#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define maxsonglength 100
#define maxartistlength 100
#define max_entries 3000

typedef struct{
    char song[maxsonglength];
    char artist[maxartistlength];
    int releaseyear;
}SongInfo;

void bubbleSort(SongInfo arr[], int n){
    int i,j;
    SongInfo temp;
    for(i=0;i<n-1;i++)
        for(j=1;j<n-i-1;j++)
            if(strcmp(arr[j].song,arr[j+1].song)>0)
                {
                    temp=arr[j];
                    arr[j]=arr[j+1];
                    arr[j+1]=temp;
                }
}

int cmpSongName(const void *a,const void *b){
    return strcmp(((SongInfo *)a)->song,((SongInfo *)b)->song);
}
int main(int argc, char *argv[]){
    if(argc!=3){
        printf("Usage: %s <file-path><year>\n", argv[0]);
        return 1;
    }
    char *filepath = argv[1];
    int target_year=atoi(argv[2]);
    FILE *file = fopen(filepath,"r");
    if(file==NULL){
        perror("Error oppening the csv file");
        exit(1);
    }
    SongInfo songs[max_entries];
    int num_songs=0;
    char line[maxsonglength+maxartistlength+10];
    while (fgets(line,sizeof(line),file)){
        char *token=strtok(line,",");

        if(token==NULL) continue;  

        strcpy(songs[num_songs].song,token);

        token=strtok(NULL,",");

        if(token==NULL) continue;  

        strcpy(songs[num_songs].artist,token);

        token=strtok(NULL,",");

        if(token==NULL) continue;

        songs[num_songs].releaseyear=atoi(token);

        num_songs++;

        if(num_songs>=max_entries){
            printf("Exceeded max nr of entries.\n");
            break;
        }
    }
    fclose(file);

    clock_t start_qsort=clock();
    qsort(songs,num_songs,sizeof(SongInfo),cmpSongName);
    clock_t end_qsort=clock();
    printf("Execution time for qsort %ld\n",end_qsort-start_qsort);
    
    clock_t start_bubblesort=clock();
    bubbleSort(songs,num_songs);
    clock_t end_bubblesort=clock();
    printf("Execution time for bubble sort %ld\n",end_bubblesort-start_bubblesort);
     for(int i=0;i<num_songs;i++)
        {
            if(songs[i].releaseyear==target_year)
                printf("<%s> by <%s> released in <%d>\n",songs[i].song,songs[i].artist,songs[i].releaseyear);
        }
    return 0;
}