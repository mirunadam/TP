#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define RED 0
#define YELLOW 1
#define BLACK 2
#define BLUE 3
#define DARK_B 4

#define colorRED     "\x1b[31m"
#define colorGREEN   "\x1b[32m"
#define colorYELLOW  "\x1b[33m"
#define colorMAGENTA "\x1b[35m"
#define colorBLUE    "\x1b[34m"
#define colorDARKBLUE "\x1b[36m"
#define RESET        "\x1b[0m"
#define W_HIGHLIGHT  "\x1b[47m"
#define END_HIGHLIGHT "\x1b[0m"

int fp_token = 1;

typedef struct {
    int wall[5][5];
    int first_l;
    int second_l[2];
    int third_l[3];
    int four_l[4];
    int five_l[5];
    int score;
    int penalty[7];
} player_board;

int bag[5];
int factory_display[5][4] = {0};
int middle_area[6];

char *find_color(int j) {
    switch (j) {
        case RED:
            return colorRED;
        case YELLOW:
            return colorYELLOW;
        case BLACK:
            return colorMAGENTA;
        case BLUE:
            return colorBLUE;
        case DARK_B:
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
    middle_area[5] = 1; //for the fp token
    for (i = 0; i < 5; i++) {
        middle_area[i] = 0;
    }
}

void add_tiles_to_middle_area(int middle_area[], int color, int count) {
    middle_area[color] += count;
}

void print_middle_area(int middle_area[]) {
    printf("            MIDDLE AREA         \n");
    if (middle_area[5]) {
        printf(colorGREEN "     FP TOKEN\n");
    }
    for (int i = 0; i < 5; i++) {
        if (middle_area[i] != 0) {
            char *COLOR = find_color(i);
            printf("%s%d tiles \n", COLOR, middle_area[i]);
        }
    }
    printf(RESET "\n=^..^=   =^..^=   =^..^=    =^..^=    =^..^=    =^..^=    =^..^=\n");
    printf("\n");
}

void extract_random_tiles(int bag[], int factory_display[][4]) {
    int i, j;
    for (int fd_count = 0; fd_count < 5; fd_count++) {
        for (i = 0; i < 4; i++) {
            do {
                j = rand() % 5;
            } while (bag[j] == 0);
            bag[j]--;
            factory_display[fd_count][i] = j;
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

    board->score = 0;

    for (int i = 0; i < 7; i++) {
        board->penalty[i] = 0;
    }
}

int scoring(int penalty[]) {
    int score = 0;
    for (int i = 0; i < 7; i++) {
        int j = i + 1;
        if ((j == 1 || j == 2) && penalty[i] != 0) {
            score--;
        } else if ((j == 3 || j == 4 || j == 5) && penalty[i] != 0) {
            score -= 2;
        } else if ((j == 6 || j == 7) && penalty[i] != 0) {
            score -= 3;
        }
    }
    return score;
}

void printHighlighted(int tile, int color) {
    char *highlighter;
    switch (color) {
        case RED:
            highlighter = "\x1b[41m"; // Red background
            break;
        case YELLOW:
            highlighter = "\x1b[43m"; // Yellow background
            break;
        case BLACK:
            highlighter = "\x1b[45m"; // Magenta background
            break;
        case BLUE:
            highlighter = "\x1b[44m"; // Dark Blue background
            break;
        case DARK_B:
            highlighter = "\x1b[46m"; // Blue background
            break;
        default:
            highlighter = "\x1b[47m"; // Default white background
            break;
    }
    printf("%s%d \x1b[0m", highlighter, tile);
}

char *board_color_pattern(int i, int j) {
    if (i == j) {
        return "\x1b[44m"; // Dark blue
    } else if ((i == 0 && j == 4) || j + 1 == i) {
        return "\x1b[46m"; // Blue background
    } else if ((i == 4 && j == 0) || j == i + 1) {
        return "\x1b[43m"; // Yellow background
    } else if ((i == 3 && j == 0) || (i == 4 && j == 1) || (j == i + 2)) {
        return "\x1b[41m"; // Red background
    } else {
        return "\x1b[45m"; // Magenta background
    }
}

void print_board(player_board *board) {
    printf("        Player's Board (Wall):  \n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            char *highlit = board_color_pattern(i, j);
            printf("%s", highlit);
            printHighlighted(board->wall[i][j], board->wall[i][j]);
            printf(RESET);
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

    printf("\nScore: %d\n", board->score);

    printf("\nPenalties:\n");
    for (int i = 0; i < 7; i++) {
        printf("%d ", board->penalty[i]);
    }
    printf("\n");
}

// Function to read user selection for location (factory displays or middle area) and color
void read_user_selection(int *location, int *color) {
    printf("Enter location (0 for middle area, 1 for factory displays): ");
    scanf("%d", location);

    printf("Enter color (0 for Red, 1 for Yellow, 2 for Black, 3 for Blue, 4 for Dark Blue): ");
    scanf("%d", color);
}

// Function to add a tile to the middle area
void add_tile_to_middle_area(int middle_area[], int color) {
    middle_area[color]++;
}

// Function to remove a tile from a factory display
void remove_tile_from_factory_display(int factory_display[][4], int factory_index, int tile_index) {
    factory_display[factory_index][tile_index] = -1;
}

// Function to remove a tile from the middle area
void remove_tile_from_middle_area(int middle_area[], int color) {
    middle_area[color]--;
}

// Function to add a tile to a pattern line
void add_tile_to_pattern_line(player_board *board, int pattern_line, int color) {
    switch (pattern_line) {
        case 0:
            board->first_l = color;
            break;
        case 1:
            for (int i = 0; i < 2; i++) {
                if (board->second_l[i] == 0) {
                    board->second_l[i] = color;
                    break;
                }
            }
            break;
        case 2:
            for (int i = 0; i < 3; i++) {
                if (board->third_l[i] == 0) {
                    board->third_l[i] = color;
                    break;
                }
            }
            break;
        case 3:
            for (int i = 0; i < 4; i++) {
                if (board->four_l[i] == 0) {
                    board->four_l[i] = color;
                    break;
                }
            }
            break;
        case 4:
            for (int i = 0; i < 5; i++) {
                if (board->five_l[i] == 0) {
                    board->five_l[i] = color;
                    break;
                }
            }
            break;
        default:
            printf("Invalid pattern line!\n");
            break;
    }
}

// Function to add a tile to the floor line
void add_tile_to_floor_line(player_board *board, int color) {
    for (int i = 0; i < 7; i++) {
        if (board->penalty[i] == 0) {
            board->penalty[i] = color;
            break;
        }
    }
}

// Function to validate if a tile can be placed on a pattern line
bool validate_placement(player_board *board, int pattern_line, int color) {
    switch (pattern_line) {
        case 0:
            return board->first_l == 0;
        case 1:
            for (int i = 0; i < 2; i++) {
                if (board->second_l[i] == color) return false;
            }
            return true;
        case 2:
            for (int i = 0; i < 3; i++) {
                if (board->third_l[i] == color) return false;
            }
            return true;
        case 3:
            for (int i = 0; i < 4; i++) {
                if (board->four_l[i] == color) return false;
            }
            return true;
        case 4:
            for (int i = 0; i < 5; i++) {
                if (board->five_l[i] == color) return false;
            }
            return true;
        default:
            return false;
    }
}

int main() {
    player_board board;
    srand(time(NULL));
    initialize_bag(bag);
    extract_random_tiles(bag, factory_display);
    initialize_middle_area(middle_area);
    add_tiles_to_middle_area(middle_area, BLUE, 3);

    print_middle_area(middle_area);
    print_factory_display(factory_display);
    initialize_player_board(&board);
    print_bag_contents(bag);
    print_board(&board);

    int location, color, factory_index, pattern_line;

    read_user_selection(&location, &color);

    if (location == 0) {
        add_tile_to_middle_area(middle_area, color);
    } else if (location == 1) {
        printf("Enter the factory display number (1 to 5): ");
        scanf("%d", &factory_index);
        factory_index--; // Decrement by 1 to match array indexing

        // Find the first available tile of the chosen color in the factory display
        int tile_index = -1;
        for (int i = 0; i < 4; i++) {
            if (factory_display[factory_index][i] == color) {
                tile_index = i;
                break;
            }
        }
        if (tile_index == -1) {
            printf("The chosen color is not available in the selected factory display.\n");
            return 1; // Exit with error code 1
        }

        // Remove the tile from the factory display
        remove_tile_from_factory_display(factory_display, factory_index, tile_index);

        printf("Enter the pattern line number (1 to 5) to place the tiles: ");
        scanf("%d", &pattern_line);
        pattern_line--; // Decrement by 1 to match array indexing

        // Validate if the placement is valid
        if (validate_placement(&board, pattern_line, color)) {
            add_tile_to_pattern_line(&board, pattern_line, color);
        } else {
            printf("Invalid placement on the chosen pattern line.\n");
            return 1; // Exit with error code 1
        }
    } else {
        printf("Invalid location.\n");
        return 1; // Exit with error code 1
    }

    print_factory_display(factory_display);
    print_board(&board);

    return 0;
}
