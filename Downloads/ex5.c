#include <stdio.h>
#include <stdlib.h>

void remove_text_formating(FILE *input, FILE *output){
    int c;
    while ((c = getc(input)) != EOF) {
        if (c == '<') {
            while ((c = getc(input)) != EOF && c != '>');
        } else {
            fputc(c, output);
        }
    }

}
void shift_timings(int added_s, FILE *input, FILE *output){
    int  h1, m1, s1, ms1, h2, m2, s2, ms2;
    fscanf(input, "%d:%d:%d,%d --> %d:%d:%d,%d", &h1, &m1, &s1, &ms1, &h2, &m2, &s2, &ms2);
    
    int total_time1 = h1 * 3600 + m1 * 60 + s1 + added_s;
    h1 = total_time1/3600;
    total_time1 %= 3600;
    m1 = total_time1 / 60;
    s1 = total_time1 % 60;

    int total_time2 = h2 * 3600 + m2 * 60 + s2 + added_s;
    h2 = total_time2/3600;
    total_time2 %= 3600;
    m2 = total_time2 / 60;
    s2 = total_time2 % 60;

    fprintf(output, "%02d:%02d:%02d,%03d --> %02d:%02d:%02d,%03d", h1, m1, s1, ms1, h2, m2, s2, ms2);
}
 void shift_seconds(int added_s, FILE *input, FILE *output){
    int  h1, m1, s1, ms1, h2, m2, s2, ms2;
    while(fscanf(input, "%d:%d:%d,%d --> %d:%d:%d,%d", &h1, &m1, &s1, &ms1, &h2, &m2, &s2, &ms2)== 8){
        s1=s1+added_s;
        s2=s2+added_s;
        fprintf(output, "%02d:%02d:%02d,%03d --> %02d:%02d:%02d,%03d", h1, m1, s1, ms1, h2, m2, s2, ms2);
    }
 }

int main(int argc, char **argv){
    int s=atoi(argv[3]); 
    if(argc<3){
        perror("ERROR no input files");
        exit(EXIT_FAILURE);
    }
    FILE *input=fopen(argv[1], "r");
    FILE *output=fopen(argv[2], "w");
    if(input == NULL){
        perror("ERROR input file dosent exist");
        exit(EXIT_FAILURE);
    }
    if(output == NULL){
        perror("ERROR input file dosent exist");
        exit(EXIT_FAILURE);
    }
    shift_seconds(s, input, output);
    remove_text_formating(input, output);
    fclose(input);
    fclose(output);
    return 0;
}