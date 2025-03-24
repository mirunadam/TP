#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RED 0
#define YELLOW 1
#define BLACK 2
#define BLUE 3
#define DARK_B 4

#define colorRED     "\x1b[31m"
#define colorGREEN   "\x1b[32m"
#define colorYELLOW  "\x1b[33m"
#define colorMAGENTA "\x1b[35m" //instead of black
#define colorDARKBLUE    "\x1b[34m"
#define colorBLUE "\x1b[36m"

#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

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

char *find_color(int j) {
    switch (j) {
        case 0:
            return colorRED;
        case 1:
            return colorYELLOW;
        case 2:
            return colorMAGENTA;
        case 3:
            return colorBLUE;
        case 4:
            return colorDARKBLUE;
        default:
            return NULL; //for unknown color
    }
}

void initialize_bag(int bag[]) {
    int i;
    for (i = 0; i < 5; i++) {
        bag[i] = 20;
    }
}

void print_bag_contents(int bag[]) {
    printf("        BAG CONTENTS:\n");
    printf(colorRED "Red: %d\n", bag[RED]);
    printf(colorYELLOW "Yellow: %d\n", bag[YELLOW]);
    printf(colorMAGENTA "Black: %d\n", bag[BLACK]);
    printf(colorBLUE "Blue: %d\n", bag[BLUE]);
    printf(colorDARKBLUE "Dark Blue: %d\n", bag[DARK_B]);

    printf(RESET "\n=^..^=   =^..^=   =^..^=    =^..^=    =^..^=    =^..^=    =^..^=\n");
    printf("\n");

}


void initialize_middle_area(int middle_area[]) {
    int i;
    middle_area[5]=1; //for the fp token
    for (i = 0; i < 5; i++) {
        middle_area[i] = 0;
    }
}

void add_tiles_to_middle_area(int middle_area[], int color, int count) {
    middle_area[color] += count;
}


void print_middle_area(int middle_area[]){
    printf("            MIDDLE AREA         \n");
    if(middle_area[5]){
        printf(colorGREEN "     FP TOKEN\n");
    }
    for (int i = 0; i < 5; i++) {
        if(middle_area[i] != 0){
            char * COLOR = find_color(i);
            printf("%s%d tiles \n", COLOR, middle_area[i]);
        }
        
    }

    printf(RESET "\n=^..^=   =^..^=   =^..^=    =^..^=    =^..^=    =^..^=    =^..^=\n");
    printf("\n");
}


void extract_random_tiles(int bag[], int factory_display[][4]) {
    int i, j;
    for(int fd_count=0; fd_count < 5; fd_count++ ){
        for (i = 0; i < 4; i++) {
            do {
                j = rand() % 5; 
            }  while (bag[j] == 0); 
            //int color = find_color(j);
            bag[j]--;
            factory_display[fd_count][i]=j;
        }
    }
}

void take_tiles_from_factory(int factory_display[][4], int index, int color, player_board *board) {
    for (int i = 0; i < 4; i++) {
        if (factory_display[index][i] == color) {
            switch (color) {
                case RED:
                    board->first_l++;
                    break;
                case YELLOW:
                    board->second_l[i]++;
                    break;
                case BLACK:
                    board->third_l[i]++;
                    break;
                case BLUE:
                    board->four_l[i]++;
                    break;
                case DARK_B:
                    board->five_l[i]++;
                    break;
                default:
                    // Handle unknown color
                    break;
            }
            // Remove the tile from the factory display
            factory_display[index][i] = -1;
        }
    }
}


void print_factory_display(int factory_display[][4]) {
    for (int fd_count = 0; fd_count < 5; fd_count++) { 
        printf("    ~ Factory Display %d ~\n", fd_count + 1);
        for (int i = 0; i < 4; i++) { 
            switch (factory_display[fd_count][i]) {
                case RED:
                    printf(colorRED "Tile %d: Red\n", i + 1);
                    printf(RESET);
                    break;
                case YELLOW:
                    printf(colorYELLOW "Tile %d: Yellow\n", i + 1);
                    printf(RESET);
                    break;
                case BLACK:
                    printf(colorMAGENTA "Tile %d: Black\n", i + 1);
                    printf(RESET);
                    break;
                case BLUE:
                    printf(colorBLUE "Tile %d: Blue\n", i + 1);
                    printf(RESET);
                    break;
                case DARK_B:
                    printf(colorDARKBLUE "Tile %d: Dark Blue\n", i + 1);
                    printf(RESET);
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
    initialize_middle_area(middle_area);

    add_tiles_to_middle_area(middle_area, BLUE, 3);
    add_tiles_to_middle_area(middle_area, RED, 2);
    add_tiles_to_middle_area(middle_area, BLACK, 52);


    print_middle_area(middle_area);
    print_factory_display(factory_display);
    initialize_player_board(&board);

    print_bag_contents(bag);


    return 0;
}