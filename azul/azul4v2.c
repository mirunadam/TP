#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
/*
#define MAGENTA "\x1b[35m" 
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

#define BLUE    "\x1b[34m"
#define LIGHT_BLUE "\x1b[94m"
#define DARK_BLUE "\x1b[38;5;12m"
#define SKY_BLUE "\x1b[38;2;0;191;255m"
#define TEAL "\x1b[36m"
#define RESET   "\x1b[0m"*/

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
#define W_HIGHLIGHT "\x1b[47m"
#define END_HIGHLIGHT "\x1b[0m"
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

char* find_highlighter(int j) {
    switch (j) {
        case 0:
            return "\x1b[47m";
        case 1:
            return "\x1b[41m"; // Red background
        case 2:
            return "\x1b[43m"; // Yellow background
        case 3:
            return "\x1b[45m"; // Magenta background
        case 4:
            return "\x1b[46m"; // Blue background
        case 5:
            return "\x1b[44m"; // Dark Blue background
        default:
            return "\x1b[47m"; 
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
                    printf("Empty\n");
                    break;
            }
        
        }
        printf("\n");
    
    }
    printf(RESET "\n=^..^=   =^..^=   =^..^=    =^..^=    =^..^=    =^..^=    =^..^=\n");
    printf("\n");
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
void printHighlighted(int tile, int color) {
    char *highlighter = find_highlighter(color);
    printf("%s%d ", highlighter, tile);
    printf(RESET);
}

char *board_color_pattern(int i, int j){
    if(i==j){
        return "\x1b[44m"; //dark blue
    }
    if((i==0 && j==4) || j+1==i){
        return "\x1b[46m"; // Blue background
    }
    if((i==4 && j==0) || j==i+1){
         return "\x1b[43m"; // Yellow background
    }
    if((i==3 && j==0)||(i==4 && j==1)||(j==i+2)){
        return "\x1b[41m"; // Red background
    }
    else{
        return "\x1b[45m"; // Magenta background
    }
}

void print_board(player_board *board) {
    printf("        Player's Board (Wall):  \n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            char *highlit = board_color_pattern(i,j);
            printf( "%s%d ", highlit , board->wall[i][j]);
            //printf( "%s%d ", W_HIGHLIGHT , board->wall[i][j]);
            printf(END_HIGHLIGHT);
        }
        printf("\n");
    }

    printf(RESET "\n=^..^=   =^..^=   =^..^=    =^..^=    =^..^=    =^..^=    =^..^=\n");
    printf("\n");

    printf("\n      Pattern Lines:  \n");
    printf("1: ");
    printHighlighted(board->first_l, board->first_l);

    printf("\n2: ");
    for (int i = 0; i < 2; i++) {
        printHighlighted(board->second_l[i], board->second_l[i]);
        printf(" ");
    }

    printf("\n3: ");
    for (int i = 0; i < 3; i++) {
        printHighlighted(board->third_l[i], board->third_l[i]);
        printf(" ");
    }

    printf("\n4: ");
    for (int i = 0; i < 4; i++) {
        printHighlighted(board->four_l[i], board->four_l[i]);
        printf(" ");
    }

    printf("\n5: ");
    for (int i = 0; i < 5; i++) {
        printHighlighted(board->five_l[i], board->five_l[i]);
        printf(" ");
    }
printf("\n");

printf(RESET "\n=^..^=   =^..^=   =^..^=    =^..^=    =^..^=    =^..^=    =^..^=\n");
printf("\n");

printf("\nPenalties:\n");
    for (int i = 0; i < 7; i++) {
        printf("%d ", board->penalty[i]);
    }
    printf("\nScore: %d\n", board->score);

    printf("\n");
}

void print_pattern_lines(player_board *board) {
     printf("\n      Pattern Lines:  \n");
    printf("1: ");
    printHighlighted(board->first_l, board->first_l);

    printf("\n2: ");
    for (int i = 0; i < 2; i++) {
        printHighlighted(board->second_l[i], board->second_l[i]);
        printf(" ");
    }

    printf("\n3: ");
    for (int i = 0; i < 3; i++) {
        printHighlighted(board->third_l[i], board->third_l[i]);
        printf(" ");
    }

    printf("\n4: ");
    for (int i = 0; i < 4; i++) {
        printHighlighted(board->four_l[i], board->four_l[i]);
        printf(" ");
    }

    printf("\n5: ");
    for (int i = 0; i < 5; i++) {
        printHighlighted(board->five_l[i], board->five_l[i]);
        printf(" ");
    }
printf("\n");


    printf(RESET "\n=^..^=   =^..^=   =^..^=    =^..^=    =^..^=    =^..^=    =^..^=\n");
    printf("\n");
}

bool validate_placement(player_board *board, int pattern_line, int color) {
    int color_already;
    switch (pattern_line) {
        case 0:
            if(board->first_l!=0)
                return false;
            else return true;
        case 1:
            for (int i = 0; i < 2; i++) {
                if (board->second_l[i] != 0){
                    color_already = board->second_l[i];
                    if(color_already==color){
                        return true;
                    }
                    else return false;
                }
                else return true; 
            }
        case 2:
            for (int i = 0; i < 3; i++) {
                if (board->third_l[i] != 0){
                    color_already = board->third_l[i];
                    if(color_already==color){
                        return true;
                    }
                    else return false;
                } 
                else return true;
            }
        case 3:
            for (int i = 0; i < 4; i++) {
                if (board->four_l[i] != 0){
                    color_already = board->four_l[i];
                    if(color_already==color){
                        return true;
                    }
                    else return false;
                }
                else return true; 
            }
        case 4:
            for (int i = 0; i < 5; i++) {
                if (board->five_l[i] != 0){
                    color_already = board->five_l[i];
                    if(color_already==color){
                        return true;
                    }
                    else return false;
                } 
                else return true;
            }
        default:
            return false;
    }
}

void add_tiles_to_pattern_lines(player_board *board, int pattern_line, int color){
    switch (pattern_line) {
        case 0:
            if(validate_placement(board, pattern_line, color)){
                board->first_l = color;
                break;
            }else printf("INVALID LOCATION");
            break;

        case 1:
            for (int i = 0; i < 2; i++) {
                if (board->second_l[i] == 0 && validate_placement(board, pattern_line, color)) {
                    board->second_l[i] = color;
                    break;
                }
                else printf("INVALID LOCATION\n");
            }
            break;
        case 2:
            for (int i = 0; i < 3; i++) {
                if (board->third_l[i] == 0 && validate_placement(board, pattern_line, color)) {
                    board->third_l[i] = color;
                    break;
                }
                else printf("INVALID LOCATION");
            }
            break;
        case 3:
            for (int i = 0; i < 4; i++) {
                if (board->four_l[i] == 0 && validate_placement(board, pattern_line, color)) {
                    board->four_l[i] = color;
                    break;
                }
                else printf("INVALID LOCATION");
            }
            break;
        case 4:
            for (int i = 0; i < 5; i++) {
                if (board->five_l[i] == 0 && validate_placement(board, pattern_line, color)) {
                    board->five_l[i] = color;
                    break;
                }
                else printf("INVALID LOCATION");
            }
            break;
        default:
            printf("Invalid pattern line!\n");
            break;
    }

}


void print_all(player_board *board){
    print_middle_area(middle_area);
    print_factory_display(factory_display);
    print_board(board);
}

void read_selection(player_board *board, int factory_display[][4], int middle_area[]) {
    int factory_index, pattern_line, option;
    int color;
    
    printf("Choose from factory displays(1) or middle area(0)?");
    scanf("%d", &option);

    // Ask the user to choose a factory display
    if(option){
        printf("Enter the factory display number (1 to 5): ");
        scanf("%d", &factory_index);
        factory_index--; // Decrement by 1 to match array indexing
    
    // Ask the user to choose a tile index from the chosen factory display
        printf("1-red, 2-yellow, 3-magenta, 4-blue, 5-dark blue\n");
        printf("Enter the color: ");
        scanf("%d", &color);
    //tile_index--; // Decrement by 1 to match array indexing
    
    // Ask the user to choose a pattern line to place the tile
        printf("Enter the pattern line number (1 to 5) to place the tiles: ");
        scanf("%d", &pattern_line);
        pattern_line--; // Decrement by 1 to match array indexing
        for(int i=0; i<4; i++){
            if(factory_display[factory_index][i]+1==color){
                add_tiles_to_pattern_lines(board, pattern_line, color);
            }
            else{
                add_tiles_to_middle_area(middle_area, factory_display[factory_index][i], 1);
            }
            factory_display[factory_index][i]=-1;
        }
    }else{ //implement for taking from the middle ground
        printf("1-red, 2-yellow, 3-magenta, 4-blue, 5-dark blue\n");
        printf("Enter the color: ");
        scanf("%d", &color);
    //tile_index--; // Decrement by 1 to match array indexing
    
    // Ask the user to choose a pattern line to place the tile
        printf("Enter the pattern line number (1 to 5) to place the tiles: ");
        scanf("%d", &pattern_line);
        pattern_line--;

        middle_area[5]=0; //replace the fp token
        board->penalty[0]=1;

        while(middle_area[color-1]!=0){
            add_tiles_to_pattern_lines(board, pattern_line, color);
            middle_area[color-1]--;
        }
    }
    
    //print_all(board);
}

bool check_horizontal_completion(player_board *board) {
    // Check rows
    for (int i = 0; i < 5; i++) {
        int count = 0;
        int color = board->wall[i][0]; // First color in the row
        if (color != 0) {
            for (int j = 1; j < 5; j++) {
                if (board->wall[i][j] == color)
                    count++;
                else
                    break;
            }
            if (count == 4) // 5 consecutive tiles
                return true;
        }
    }

    // Check columns
    for (int j = 0; j < 5; j++) {
        int count = 0;
        int color = board->wall[0][j]; // First color in the column
        if (color != 0) {
            for (int i = 1; i < 5; i++) {
                if (board->wall[i][j] == color)
                    count++;
                else
                    break;
            }
            if (count == 4) // 5 consecutive tiles
                return true;
        }
    }

    return false; // No horizontal completion
}

void prepare_next_round(player_board *board, int factory_display[][4], int middle_area[]) {
    char ans;
    printf("Do you want to continue? (y/n) ");
    scanf(" %c", &ans);
    if (ans == 'y') {
        if (!check_horizontal_completion(board)) {
            printf("No horizontal line of 5 consecutive tiles has been completed. Preparing next round...\n");
            extract_random_tiles(bag, factory_display);
            print_middle_area(middle_area);
            print_factory_display(factory_display);
        } else {
            printf("At least one player has completed a horizontal line of 5 consecutive tiles on their wall. Game over.\n");
            exit(0);
        }
    } else if (ans == 'n') {
        printf("Exiting the game.\n");
        exit(0);
    } else {
        printf("Invalid input. Please enter 'y' or 'n'.\n");
        // Call prepare_next_round again recursively to prompt the user for correct input
        prepare_next_round(board, factory_display, middle_area);
    }
}



void add_tile_to_floor_line(player_board *board, int color) {
    for (int i = 0; i < 7; i++) {
        if (board->penalty[i] == 0) {
            board->penalty[i] = color;
            break;
        }
    }
}


int main() {

    player_board board;
    srand(time(NULL));
    initialize_bag(bag);
    extract_random_tiles(bag, factory_display);
    initialize_middle_area(middle_area);

    //add_tiles_to_middle_area(middle_area, BLUE, 3);
   // add_tiles_to_middle_area(middle_area, RED, 2);
   // add_tiles_to_middle_area(middle_area, BLACK, 52);


    /*print_middle_area(middle_area);
    print_factory_display(factory_display);
    initialize_player_board(&board);

    print_bag_contents(bag);

    add_tiles_to_pattern_lines(&board, 2, BLUE);

    print_board(&board);
    read_selection(&board, factory_display, middle_area);*/

    while (true) {
        print_middle_area(middle_area);
        print_factory_display(factory_display);
        print_board(&board);
        read_selection(&board, factory_display, middle_area);
        prepare_next_round(&board, factory_display, middle_area);
    }
    

    return 0;
}