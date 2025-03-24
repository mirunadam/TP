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
    printf(colorMAGENTA "Magenta: %d\n", bag[BLACK]);
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
                    printf(colorMAGENTA "Tile %d: Magenta\n", i + 1);
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

int deduct_score_from_penalty_line(int penalty[], int score){

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

void add_tile_to_floor_line(player_board *board, int color);

bool validate_placement(player_board *board, int pattern_line, int color) {
    int color_already;
    switch (pattern_line) {
        case 0:
            if(board->first_l!=0)
            { 
                return false;
            }
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
void add_tiles_to_pattern_lines(player_board *board, int pattern_line, int color);

void choose_another_line(player_board *board, int color){
    int pattern_line;
    printf("Enter the pattern line number (1 to 5) to place the tiles: ");
        scanf("%d", &pattern_line);
        pattern_line--; 
    for(int i=0; i<4; i++){
        add_tiles_to_pattern_lines(board, pattern_line, color);
    }
}

void place_excess_tiles(player_board *board, int pattern_line, int color);

void add_tiles_to_pattern_lines(player_board *board, int pattern_line, int color){
    switch (pattern_line) {
        case 0:
            if(validate_placement(board, pattern_line, color)){
                //board->first_l = color;
                place_excess_tiles(board, pattern_line, color);
                break;
            }else  place_excess_tiles(board, pattern_line, color);
            break;

        case 1:
            for (int i = 0; i < 2; i++) {
                if (/*board->second_l[i] == 0 &&*/ validate_placement(board, pattern_line, color)) {
                    //board->second_l[i] = color;
                    place_excess_tiles(board, pattern_line, color);
                    break;
                }
                else {
                    place_excess_tiles(board, pattern_line, color);
                    //printf("INVALID LOCATION\n");
                    //choose_another_line(board, color);
                }
            }
            break;
        case 2:
            for (int i = 0; i < 3; i++) {
                if (/*board->third_l[i] == 0 &&*/ validate_placement(board, pattern_line, color)) {
                    place_excess_tiles(board, pattern_line, color);
                    //board->third_l[i] = color;
                    break;
                }
                else {
                    place_excess_tiles(board, pattern_line, color);
                    //printf("INVALID LOCATION\n");
                    //choose_another_line(board, color);
                }
            }
            break;
        case 3:
            for (int i = 0; i < 4; i++) {
                if (/*board->four_l[i] == 0 &&*/ validate_placement(board, pattern_line, color)) {
                    place_excess_tiles(board, pattern_line, color);
                    //board->four_l[i] = color;
                    break;
                }
                else {
                    place_excess_tiles(board, pattern_line, color);
                    //printf("INVALID LOCATION\n");
                    //choose_another_line(board, color);
                }
            }
            break;
        case 4:
            for (int i = 0; i < 5; i++) {
                if (/*board->five_l[i] == 0 &&*/ validate_placement(board, pattern_line, color)) {
                    //board->five_l[i] = color;
                    place_excess_tiles(board, pattern_line, color);
                    break;
                }
                else {
                    place_excess_tiles(board, pattern_line, color);
                    //printf("INVALID LOCATION\n");
                    //choose_another_line(board, color);
                }
            }
            break;
        default:
            printf("Invalid pattern line!\n");
            break;
    }

}


void print_all(player_board *board){
    print_board(board);
}

void place_excess_tiles(player_board *board, int pattern_line, int color) {
    switch (pattern_line) {
        case 0:
            if (board->first_l == 0) {
                board->first_l = color;
                //printf("debbbug1");
            } else {
                add_tile_to_floor_line(board, color);
                //printf("debbbug2");
            }
            break;
        case 1:
            if (board->second_l[0] == 0) {
                board->second_l[0] = color;
            } else if (board->second_l[1] == 0) {
                board->second_l[1] = color;
            } else {
                add_tile_to_floor_line(board, color);
            }
            break;
        case 2:
            if (board->third_l[0] == 0) {
                board->third_l[0] = color;
            } else if (board->third_l[1] == 0) {
                board->third_l[1] = color;
            } else if (board->third_l[2] == 0) {
                board->third_l[2] = color;
            } else {
                add_tile_to_floor_line(board, color);
            }
            break;
        case 3:
            if (board->four_l[0] == 0) {
                board->four_l[0] = color;
            } else if (board->four_l[1] == 0) {
                board->four_l[1] = color;
            } else if (board->four_l[2] == 0) {
                board->four_l[2] = color;
            } else if (board->four_l[3] == 0) {
                board->four_l[3] = color;
            } else {
                add_tile_to_floor_line(board, color);
            }
            break;
        case 4:
            if (board->five_l[0] == 0) {
                board->five_l[0] = color;
            } else if (board->five_l[1] == 0) {
                board->five_l[1] = color;
            } else if (board->five_l[2] == 0) {
                board->five_l[2] = color;
            } else if (board->five_l[3] == 0) {
                board->five_l[3] = color;
            } else if (board->five_l[4] == 0) {
                board->five_l[4] = color;
            } else {
                add_tile_to_floor_line(board, color);
            }
            break;
        default:
            printf("Invalid pattern line!\n");
            break;
    }
}


void read_selection(player_board *board, int factory_display[][4], int middle_area[]) {
    int factory_index, pattern_line, option;
    int color;
    
    printf("Choose from factory displays(1) or middle area(0)?");
    scanf("%d", &option);


    if(option){
        printf("Enter the factory display number (1 to 5): ");
        scanf("%d", &factory_index);
        factory_index--; 
    

        printf("1-red, 2-yellow, 3-magenta, 4-blue, 5-dark blue\n");
        printf("Enter the color: ");
        scanf("%d", &color);
    
    
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
        //place_excess_tiles(board, pattern_line, color);
    }else{ // for taking from the middle ground
        printf("1-red, 2-yellow, 3-magenta, 4-blue, 5-dark blue\n");
        printf("Enter the color: ");
        scanf("%d", &color);

        printf("Enter the pattern line number (1 to 5) to place the tiles: ");
        scanf("%d", &pattern_line);
        pattern_line--;

        middle_area[5]=0; //replace the fp token
        board->penalty[0]=1;

        while(middle_area[color-1]!=0){
            add_tiles_to_pattern_lines(board, pattern_line, color);
            middle_area[color-1]--;
        }
        //place_excess_tiles(board, pattern_line, color);
    }

    
    print_all(board);
}

void add_tile_to_floor_line(player_board *board, int color) {
    for (int i = 0; i < 7; i++) {
        if (board->penalty[i] == 0) {
            board->penalty[i] = color;
            break;
        }
    }
}

bool is_round_over(int factory_display[][4], int middle_area[]) {
    // Check if all factory displays and the middle area are empty
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 4; j++) {
            if (factory_display[i][j] != -1) // If any factory display still has tiles
                return false;
        }
    }
    // check if the middle area is empty
    for (int i = 0; i < 5; i++) {
        if (middle_area[i] != 0)
            return false;
    }
    // if everything is empty, the round is over
    return true;
}

void prepare_next_round(int factory_display[][4], int bag[]) {
    // Refill the bag if it's empty
    bool bag_empty = true;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 4; j++) {
            if (factory_display[i][j] != -1) { // If any factory display still has tiles
                bag_empty = false;
                break;
            }
        }
        if (!bag_empty)
            break;
    }

    if (bag_empty) {
        // Refill bag with all tiles from lid of game box
        initialize_bag(bag);
    }

    // Refill factory displays with 4 tiles each
    extract_random_tiles(bag, factory_display);
}

bool check_line_full(player_board *board, int line) {
    switch (line) {
        case 0: // First line
                if (board->first_l == 0) // If any spot is empty, the line isn't full
                    return false;
            return true; // All spots filled
        case 1: // Second line
            for (int i = 0; i < 2; i++) {
                if (board->second_l[i] == 0) // If any spot is empty, the line isn't full
                    return false;
            }
            return true; // All spots filled
        case 2: // Third line
            for (int i = 0; i < 3; i++) {
                if (board->third_l[i] == 0) // If any spot is empty, the line isn't full
                    return false;
            }
            return true; // All spots filled
        case 3: // Fourth line
            for (int i = 0; i < 4; i++) {
                if (board->four_l[i] == 0) // If any spot is empty, the line isn't full
                    return false;
            }
            return true; // All spots filled
        case 4: // Fifth line
            for (int i = 0; i < 5; i++) {
                if (board->five_l[i] == 0) // If any spot is empty, the line isn't full
                    return false;
            }
            return true; // All spots filled
        default:
            return false; // Invalid line number
    }
}
/*
void fill_board_color(player_board *board, int i, int j){
    if(i==j){
        board->wall[i][j]=5; //dark blue
    }
    if((i==0 && j==4) || j+1==i){
        board->wall[i][j]=4; // Blue background
    }
    if((i==4 && j==0) || j==i+1){
        board->wall[i][j]=2; // Yellow background
    }
    if((i==3 && j==0)||(i==4 && j==1)||(j==i+2)){
        board->wall[i][j]=1; // Red background
    }
    else{
        board->wall[i][j]=3; // Magenta background
    }
}*/

void fill_board_color2(player_board *board, int line, int color){
    switch (line)
    {
    case 0:
        if(color==5)
            board->wall[line][0]=5;
        else if(color==2)
            board->wall[line][1]=2;
        else if(color==1)
            board->wall[line][2]=1;
        else if(color==3)
            board->wall[line][3]=3;
        else if(color==4)
            board->wall[line][4]=4;    
        break;
    case 1:
        if(color==4)
            board->wall[line][0]=4;
        else if(color==5)
            board->wall[line][1]=5;
        else if(color==2)
            board->wall[line][2]=2;
        else if(color==1)
            board->wall[line][3]=1;
        else if(color==3)
            board->wall[line][4]=3;    
        break;
    case 2:
        if(color==3)
            board->wall[line][0]=3;
        else if(color==4)
            board->wall[line][1]=4;
        else if(color==5)
            board->wall[line][2]=5;
        else if(color==2)
            board->wall[line][3]=2;
        else if(color==1)
            board->wall[line][4]=1;    
        break;
    case 3:
        if(color==1)
            board->wall[line][0]=1;
        else if(color==3)
            board->wall[line][1]=3;
        else if(color==4)
            board->wall[line][2]=4;
        else if(color==5)
            board->wall[line][3]=5;
        else if(color==2)
            board->wall[line][4]=2;    
        break;
    case 4:
        if(color==2)
            board->wall[line][0]=2;
        else if(color==1)
            board->wall[line][1]=1;
        else if(color==3)
            board->wall[line][2]=3;
        else if(color==4)
            board->wall[line][3]=4;
        else if(color==5)
            board->wall[line][4]=5;    
        break;
    default:
        break;
    }
}

int color_of_the_line(player_board *board, int line){
    int color;
    switch (line)
    {
    case 0:
        color = board->first_l;
        break;
    case 1:
        color = board->second_l[0];
        break;
    case 2:
        color = board->third_l[0];
        break;
    case 3:
        color = board->four_l[0];
        break;
    case 4:
        color = board->five_l[0];
        break;
    default:
        break;
    }
    return color;
}

void free_line(player_board *board, int line){
    switch (line) {
        case 0: // First line
            board->first_l = 0;
            break;
            
        case 1: // Second line
            for (int i = 0; i < 2; i++) {
                board->second_l[i] = 0;
            }
            break;
        case 2: // Third line
            for (int i = 0; i < 3; i++) {
                board->third_l[i] = 0;
            }
            break;
        case 3: // Fourth line
            for (int i = 0; i < 4; i++) {
                board->four_l[i] = 0;
            }
            break;
        case 4: // Fifth line
            for (int i = 0; i < 5; i++) {
                board->five_l[i] = 0;
            }
            break;
        default:
            break;
    }
}

void discard_tiles_in_bag(player_board *board, int line, int color){
    switch (line)
    {   
    case 1:
        bag[color]=+1;
        break;
    case 2:
        bag[color]=+2;
        break;
    case 3:
        bag[color]=+3;
        break;
    case 4:
        bag[color]=+4;
        break;
    default:
        break;
    }
    free_line(board, line);
}

void fill_wall(player_board *board){
    int color;
    for(int i=0; i<5; i++){ //i in place of line
        if(check_line_full(board, i)){
            color = color_of_the_line(board, i);
            fill_board_color2(board, i, color);
            discard_tiles_in_bag(board, i, color);
        }
    } 
}

int main() {

    player_board board1;
    player_board board2;
    srand(time(NULL));
    initialize_bag(bag);
    extract_random_tiles(bag, factory_display);
    initialize_middle_area(middle_area);

    //add_tiles_to_middle_area(middle_area, BLUE, 3);
   // add_tiles_to_middle_area(middle_area, RED, 2);
   // add_tiles_to_middle_area(middle_area, BLACK, 52);


    //print_middle_area(middle_area);
    print_factory_display(factory_display);
    initialize_player_board(&board1);
    initialize_player_board(&board2);

    print_bag_contents(bag);

    //add_tiles_to_pattern_lines(&board, 2, BLUE);

    //print_board(&board);
    //read_selection(&board, factory_display, middle_area);
    int move = 1;
    while(!is_round_over(factory_display, middle_area)) {

        printf("Move %d\n", move);
        print_bag_contents(bag);
        print_middle_area(middle_area);
        print_factory_display(factory_display);
        printf("    PLAYER 1 BOARD  \n");
        print_board(&board1);
        printf("    PLAYER 2 BOARD  \n");
        print_board(&board2);
        if(move%2 == 1){
            printf("Player's 1 turn:\n");
            //print_all(&board1);
            read_selection(&board1, factory_display, middle_area);
            fill_wall(&board1);
        }else{
        printf("Player's 2 turn:\n");
        //print_all(&board2);
        read_selection(&board2, factory_display, middle_area);
        fill_wall(&board2);
        }
        move++;
        char choice;
        printf("Do you want to continue playing or exit? (c to continue, e to exit): ");
        scanf(" %c", &choice);

        if (choice == 'e') {
            printf("Exiting the game. Goodbye!\n");
            exit(0);
        }
    }
    printf("Round over!\n");


    return 0;
}
