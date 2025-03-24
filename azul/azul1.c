#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RED 0
#define YELLOW 1
#define BLACK 2
#define BLUE 3
#define DARK_B 4

int fp_token=1; 

typedef struct{
    int wall[5][5];
    int first_l;
    int second_l[2];
    int third_l[3];
    int four_l[4];
    int five_l[5];
    int score;
    int penalty[7];

}player_board;

int bag[5];
int factory_display[5][4] = {0};
int middle_area[6];

void initialize_bag(int bag[]) {
    int i;
    for (i = 0; i < 5; i++) {
        bag[i] = 20;
    }
}
void initialize_middle_area(int middle_area[]) {
    int i;
    middle_area[0]=1; //for the fp token
    for (i = 1; i < 6; i++) {
        middle_area[i] = 0;
    }
}

int find_color(int j) {
    switch (j) {
        case 0:
            return RED;
        case 1:
            return YELLOW;
        case 2:
            return BLACK;
        case 3:
            return BLUE;
        case 4:
            return DARK_B;
        default:
            return -1; // -1 for unknown color
    }
}
void extract_random_tiles(int bag[], int factory_display[][4]) {
    int i, j;
    for(int fd_count=0; fd_count < 5; fd_count++ ){
        for (i = 0; i < 4; i++) {
            do {
                j = rand() % 5; 
            }  while (bag[j] == 0); 
            int color = find_color(j);
            bag[j]--;
            factory_display[fd_count][i]=color;
        }
    }
}

void print_factory_display(int factory_display[][4]) {
    for (int fd_count = 0; fd_count < 5; fd_count++) { 
        printf("Factory Display %d:\n", fd_count + 1);
        for (int i = 0; i < 4; i++) { 
            switch (factory_display[fd_count][i]) {
                case RED:
                    printf("Tile %d: Red\n", i + 1);
                    break;
                case YELLOW:
                    printf("Tile %d: Yellow\n", i + 1);
                    break;
                case BLACK:
                    printf("Tile %d: Black\n", i + 1);
                    break;
                case BLUE:
                    printf("Tile %d: Blue\n", i + 1);
                    break;
                case DARK_B:
                    printf("Tile %d: Dark Blue\n", i + 1);
                    break;
                default:
                    printf("Tile %d: Unknown Color\n", i + 1);
                    break;
            }
        }
        printf("\n");
    }
}

void initialize_player_board(player_board *board) {

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            board->wall[i][j] = 0;
        }
    }

    board->first_l = 0;
    for (int i = 0; i < 2; i++) {
        board->second_l[i] = 0;
    }
    for (int i = 0; i < 3; i++) {
        board->third_l[i] = 0;
    }
    for (int i = 0; i < 4; i++) {
        board->four_l[i] = 0;
    }
    for (int i = 0; i < 5; i++) {
        board->five_l[i] = 0;
    }

    board->score=0;

    for (int i = 0; i < 7; i++) {
        board->penalty[i] = 0;
    }
}

int scoring(int penalty[] ){
    int score;
    for(int i=0; i<7; i++){
        int j=i+1;
        if((j==1 || j==2) && penalty[i]!=0){
	        score--;
        }
        if((j==3 || j==4 || j==5) && penalty[i]!=0){
	        score=score-2;
        }
        if((j==6 || j==7) && penalty[i]!=0){
	        score=score-3;
        }
    }
    return score;

}


int main(){

    player_board board;
    srand(time(NULL));
    initialize_bag(bag);
    extract_random_tiles(bag, factory_display);
    print_factory_display(factory_display);
    initialize_player_board(&board);


    return 0;
}