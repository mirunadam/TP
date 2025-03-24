#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_text_formatting(char *line, FILE *output) {
    int i = 0;
    while (line[i] != '\0') {
        if (line[i] == '<') {
            while (line[i] != '\0' && line[i] != '>')
                i++;
        } else {
            fputc(line[i], output);
        }
        i++;
    }
}

void shift_timings(int added_s, char *line, FILE *output) {
    int h1, m1, h2, m2, s1, s2, ms1, ms2;

    if (sscanf(line, "%d:%d:%d,%d --> %d:%d:%d,%d", &h1, &m1, &s1, &ms1, &h2, &m2, &s2, &ms2) == 8) {
        int total_time1 = h1 * 3600 + m1 * 60 + s1 + added_s;
        h1 = total_time1 / 3600;
        total_time1 %= 3600;
        m1 = total_time1 / 60;
        s1 = total_time1 % 60;

        int total_time2 = h2 * 3600 + m2 * 60 + s2 + added_s;
        h2 = total_time2 / 3600;
        total_time2 %= 3600;
        m2 = total_time2 / 60;
        s2 = total_time2 % 60;

        fprintf(output, "%02d:%02d:%02d,%03d --> %02d:%02d:%02d,%03d\n", h1, m1, s1, ms1, h2, m2, s2, ms2);
    }
}

int main(int argc, char **argv) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <input_file> <output_file> <seconds_to_shift>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int s = atoi(argv[3]);

    FILE *input = fopen(argv[1], "r");
    if (input == NULL) {
        perror("ERROR: Input file doesn't exist");
        exit(EXIT_FAILURE);
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL) {
        perror("ERROR: Unable to create output file");
        fclose(input);
        exit(EXIT_FAILURE);
    }

    char line[100];
    while (fgets(line, sizeof(line), input)) {
        if (strstr(line, "-->") != NULL) {
            shift_timings(s, line, output);
        } else {
            remove_text_formatting(line, output);
        }
    }

    fclose(input);
    fclose(output);
    return 0;
}
