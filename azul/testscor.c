#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


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
int fp_token=7; 

typedef struct{
    int wall[5][5];
    int first_l;
    int second_l[2];
    int third_l[3];
    int four_l[4];
    int five_l[5];
    int score;
    int penalty[7];
    int horizontal_lines_full;
    int vertical_lines_full;
    int complete_color;

}player_board;

int bag[5];
int factory_display[5][4] = {0};
int middle_area[6];

void end_game_scoring(player_board *board){

    if(check_horizontal_line_full(board)){
        int nr_horizontal=board->horizontal_lines_full;
        board->score=+(nr_horizontal*2);
    }

    if(check_vertical_line_full(board)){
        int nr_vertical=board->vertical_lines_full;
        board->score=+(nr_vertical*7);
    }

    if(check_complete_color(board)){
        int nr_colors=board->complete_color;
        board->score=+(nr_colors*10);
    }

}

int count_linked_tiles_horizontally(player_board *board, int row, int col) {
    int count = 0; // Count the initially placed tile
    int color = board->wall[row][col];

    // Check left
    for (int c = col - 1; c >= 0 && board->wall[row][c] == color; c--) {
        count++;
    }

    // Check right
    for (int c = col + 1; c < 5 && board->wall[row][c] == color; c++) {
        count++;
    }

    return count;
}

int count_linked_tiles_vertically(player_board *board, int row, int col) {
    int count = 0; // without the initially placed tile bcs we already scored that
    int color = board->wall[row][col];

    // Check up
    for (int r = row - 1; r >= 0 && board->wall[r][col] == color; r--) {
        count++;
    }

    // Check down
    for (int r = row + 1; r < 5 && board->wall[r][col] == color; r++) {
        count++;
    }

    return count;
}

void extra_score(player_board *board) {

    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 5; c++) {
            if (board->wall[r][c] != 0) {
                // Check horizontally linked tiles
                int horizontal_count = count_linked_tiles_horizontally(board, r, c);
                if (horizontal_count > 1) {
                    board->score += horizontal_count;
                }

                // Check vertically linked tiles
                int vertical_count = count_linked_tiles_vertically(board, r, c);
                if (vertical_count > 1) {
                    board->score += vertical_count;
                }
            }
        }
    }

}