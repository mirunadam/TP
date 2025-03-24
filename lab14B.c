// Row B. Sorting text Design a data structure that stores a line of text, together with its length (in characters) and number of words.
// Read all lines of a file named on the command line into an array of such structures. Sort and print the file with lines in increasing order of length,
// breaking ties first in decreasing order of words and then in alphabetical order. You may consider at most 200 lines of maximum 200 characters each.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define MAX_LINE_NUMBER 200
//maximum 200 lines in our file
#define MAX_CHAR 200
//maximum 200 characters per lines

struct Text{
    char given_text[MAX_CHAR];
    int lenght;
    int number_of_words;
};
//Text are continutul, lungimea continutului si numarul de cuvinte
int word_count(const char *string){
    int count = 0;
    bool check = true;
    
    while(*string){
        
        if(*string == ' ' || *string == '\n'){
            
            check = true;
        }
        
        else if(!check){
            
            check = false;
            count ++;
        }
        
        string++;
    }
    
    return count;
}
//functie care verifica numarul de cuvinte

int line_sort(const void *x, const void *y){
    
    struct Text *first_line = (struct Text *)x;
    struct Text *second_line = (struct Text *)y;
    //extragem stringurile din main
    
    if(first_line -> lenght > second_line -> lenght){
        return 1;
    }
    else if(first_line -> lenght < second_line -> lenght){
        return -1;
    }
    //am verificat mai intai lungimea
    else if(first_line -> number_of_words > second_line -> number_of_words){
        return 1;
    }
    else if(first_line -> number_of_words < second_line -> number_of_words){
        return -1;
    }
    //apoi am verificat numarul de cuvinte
    else return strcmp(first_line -> given_text , second_line -> given_text);
    //ultimul filtru cel alfabetic
}

int main (int argc, char *argv[])
{
    FILE *file = fopen(argv[1], "r");
    
    if(file == NULL){
        perror("Error encountered while opening the file");
        return 1;
    }
    
    struct Text lines[MAX_LINE_NUMBER];
    
    int number_of_lines = 0;
    
    while(fgets(lines[number_of_lines].given_text, MAX_CHAR, file) != NULL){
        
        lines[number_of_lines].lenght = strlen(lines[number_of_lines].given_text);
        //am extras cu strlen lungimea liniei curente
        lines[number_of_lines].number_of_words = word_count(lines[number_of_lines].given_text);
        //iar cu functia pe care am construit o anterior numarul de cuvinte
        number_of_lines ++;
    }
    fclose(file);
    
    qsort(lines, number_of_lines, sizeof(struct Text), line_sort);
    
    for(int i = 0; i < number_of_lines; i ++){
        
        printf("%s\n",lines[i].given_text );
    }
    return 0;
}
