#include <stdio.h>
#include <stdlib.h>

//programul asta numara aparitiile fiecarui caracter dintr un fisier
//am folosit vector de frecventa

//from book lab assigment 7, ex 2
/*
Write a program to read the standard input file stdin until EOF
is signaled and count the frequencies of appearances for all the
characters met. Use an array to retain the frequencies and print it
on the standard output stdout when finished. You may reuse the
code snippets from the Theoretical Summary.
*/

int main(int argc, char **argv){
    int c;
    int freq['~']= {};
    int flag=0;
    if(argc!=2){
        perror("ERROR no input file!");
        exit(EXIT_FAILURE);
    }
    FILE* f=fopen(argv[1], "rt"); //t is for text file
    if(f==NULL){
        perror("ERROR file did not open!");
        exit(EXIT_FAILURE);
    }
    while (c!=EOF){
        c=fgetc(f);
        if (c>=' '&&c<='~'){
            freq[c]++;
            flag=1;
        }
            if (flag==0){
                printf("isproblem");
            }
        }
    for (int i=' '; i<='~'; i++){
        if (freq[i]>0)
            printf("There are %d apparitions of %c\n", freq[i], i);
    }
    fclose(f);
    return 0;
}