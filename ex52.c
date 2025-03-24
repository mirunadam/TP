#include <stdio.h>
#include <stdlib.h>

void remove_text_formating(FILE *input, FILE *output) {
    int c;
    while ((c = fgetc(input)) != EOF) {
        if (c == '<') {
            while ((c = fgetc(input)) != EOF && c != '>');
        } else {
            fputc(c, output);
        }
    }
}

void shift_timings(int added_s, FILE *input, FILE *output) {
    int h1, m1, s1, h2, m2, s2;
    fscanf(input, "%d:%d:%d --> %d:%d:%d", &h1, &m1, &s1, &h2, &m2, &s2);

    // Add shift and handle overflow (more than 24 hours)
    int total_seconds = h1 * 3600 + m1 * 60 + s1 + added_s;
    int days = total_seconds / (24 * 3600); // Calculate full days to shift
    total_seconds %= (24 * 3600); // Remaining seconds within a day

    h1 = (total_seconds / 3600 + days) % 24; // Hours after adding days and handling overflow
    total_seconds %= 3600;
    m1 = total_seconds / 60;
    s1 = total_seconds % 60;

    total_seconds = h2 * 3600 + m2 * 60 + s2 + added_s;
    days = total_seconds / (24 * 3600);
    total_seconds %= (24 * 3600);

    h2 = (total_seconds / 3600 + days) % 24;
    total_seconds %= 3600;
    m2 = total_seconds / 60;
    s2 = total_seconds % 60;

    fprintf(output, "%d\n", ++h1); // Adjust subtitle number (assuming consecutive numbering)
    fprintf(output, "%02d:%02d:%02d --> %02d:%02d:%02d\n", h1, m1, s1, h2, m2, s2);
}

int main(int argc, char **argv) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <input.srt> <shift_seconds> <output.srt>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int shift_seconds = atoi(argv[2]);
    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[3], "w");

    if (input == NULL) {
        fprintf(stderr, "Error opening input file: %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    if (output == NULL) {
        fprintf(stderr, "Error opening output file: %s\n", argv[3]);
        fclose(input);
        exit(EXIT_FAILURE);
    }
    int c;
    // Combined loop for processing lines
    int line_number = 1;
    while (input != EOF) {
       
        shift_timings(shift_seconds, input, output);
        remove_text_formating(input, output);

        line_number++;
    }

    fclose(input);
    fclose(output);
    return 0;
}
