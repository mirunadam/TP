#include <stdio.h>
#include <stdlib.h>

#define MAX 30
#define BIG 10000

//problema cu orasele
// lab assign book ch greedy

int n=5;
int d[MAX][MAX]={{0, 174, 315, 634, 544}, {174, 0, 152, 544, 595}, {315, 152, 0, 393, 449}, {634, 544, 393, 0, 388},{544, 594, 449, 388, 0}}; //array with distance between points
int path[MAX];
int visited[MAX];

void choose(int last, int *distance, int *next){
    int j;
    *distance = BIG;
    *next = -1;
    for(j = 0; j < n; j++){
        if(!visited[j]){
            if(d[last][j] < *distance){
                *distance = d[last][j];
                *next = j;
            }
        }
    }
}

char *name(int i){
    switch (i)
    {
    case 0:
        /* code */
        return "Timisoara";
        break;
    case 1:
        /* code */
        return "Oradea";
        break;
    case 2:
        /* code */
        return "Cluj";
        break;
    case 3:
        /* code */
        return "Iasi";
        break;
    case 4:
        /* code */
        return "Bucuresti";
        break;
    default:
        break;
    }
    return 0;
}

int main(){

    //FILE *in;
    int i, j, cost, min, next;

    
    /*in = fopen("orase.txt", "rt");
    if(!in){
        perror("ERROR - cannot open file!");
        exit(EXIT_FAILURE);
    }
    fscanf(in, "%d", &n);

    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            fscanf(in, "%d", &(d[i][j]));
        }
    }*/

    int chosen;

    printf("we have %d city\n", n);
    printf("choose a starting city: Timisoara - 0, Oradea - 1, Cluj - 2, Iasi - 3, Bucuresti - 4\n");
    printf("choosen city is ");
    scanf("%d", &chosen);


    printf("distances between citys are:\n");

    for(i=0; i<n; i++){
        for(j=0; j<n; j++)
            printf("%d ", d[i][j]);
        printf("\n");
    }
    printf("\n");

    path[0] = chosen;
    visited[chosen] = 1;
    for(i=0; i!=chosen && i<n; i++){
        visited[i]=0;
    }
    cost=0;

    char *v, *v2;

    for(i=0; i<n-1; i++){

        choose(path[i], &min, &next);
        v=name(path[i]);
        v2=name(next);
        printf("we choose the road (%s, %s) of cost %d.\n", v, v2, min);
        path[i+1]=next;
        visited[next]=1;
        cost+=min;
    }
    //cost-=min;

    path[n]=chosen;
    //cost +=d[path[n-1]][chosen]; //aiki e cu schepsis ???!!!!
    v=name(path[n-1]);
    v2=name(chosen);
    printf("we choose the road (%s, %s) of cost %d.\n", v, v2, d[path[n-1]][chosen]);

    printf("\n the path has total length %d and is:\n", cost);
    for(i=0; i<=n; i++){
        v=name(path[i]);
        printf("%s ", v);
    }

       // printf("%d ", path[i]);
    printf("\n");

    return 0;
}
