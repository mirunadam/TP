#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
    int c;
    if(argc<3){
        perror("ERROR no input file!");
        exit(EXIT_FAILURE);
    }
    FILE* input_UNIX=fopen(argv[1], "r");
    FILE* output_DOS=fopen(argv[2], "w");
    if(input_UNIX==NULL){
        perror("ERROR input file did not open!");
        exit(EXIT_FAILURE);
    }
    if(output_DOS==NULL){
        perror("ERROR output file did not open!");
        exit(EXIT_FAILURE);
    }
    while((c=getc(input_UNIX))!=EOF){
        if(c=='\n'){
            fputc('\r', output_DOS);
            fputc(c, output_DOS);
        }
        else
            fputc(c, output_DOS);
    }
    fclose(input_UNIX);
    fclose(output_DOS);
    return 0;
}
//hexdump -C file.txt
// 0d= '\r' and 0a='\n' 
//< input.txt > output.txt
// cat /etc/passwd | program
