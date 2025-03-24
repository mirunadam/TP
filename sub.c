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
    int  h1, m1,  h2, m2;
    float s1, s2;
    char index;
    fgets(&index, sizeof(index), input);
    //while(fgets(&index, 1, input)){
        fprintf(output, "%c\n", index);
        if(fscanf(input, "%d:%d:%f --> %d:%d:%f", &h1, &m1, &s1, &h2, &m2, &s2)==6){

            double total_seconds1 = s1+added_s;
            double total_seconds2 = s2+added_s;
            if(total_seconds1>=60){
                int new_min1=m1+((int)total_seconds1)/60;
                int remaining_sec=((int)total_seconds1)%60;
                m1=new_min1;
                s1=remaining_sec;
            }else{
                s1=total_seconds1;
            }
            if(total_seconds2>=60){
                int new_min2=m2+((int)total_seconds2)/60;
                int remaining_sec=((int)total_seconds2)%60;
                m2=new_min2;
                s2=remaining_sec;
            }else{
                s2=total_seconds2;
            }  
            if(m1>=60){
                int new_hour1=h1+m1/60;
                h1=new_hour1;
                m1=m1%60;
            }
            if(m2>=60){
                int new_hour2=h2+m2/60;
                h2=new_hour2;
                m2=m2%60;
            }

        }
    //}

    fprintf(output, "%02d:%02d:%06.3f --> %02d:%02d:%06.3f\n", h1, m1, s1, h2, m2, s2);
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
    while(feof(input)==0){
        
        shift_timings(s, input, output);
        remove_text_formating(input, output);
    }
    fclose(input);
    fclose(output);
    return 0;
}