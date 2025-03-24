#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *f=fopen("./numbers.txt", "r");
    if(f == NULL){
        perror("ERROR when opening file");
        exit(EXIT_FAILURE);
    }
    int nr;
    int sum=0;
    while(fscanf(f, "%d\n", &nr) == 1){
        sum+=nr;
    }
    //printf("%d", sum);
    FILE *output = fopen("./sum.bin", "wb");
    fwrite(&sum, sizeof(sum), 1, output);
    fclose(f); //hexdump sum.bin
    //ls -la
    return 0;
}