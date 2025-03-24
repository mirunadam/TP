#include <stdio.h>
#include <stdlib.h>

#define NAME_LENGHT 50

typedef struct name{
    char surname[NAME_LENGHT];
    char first_name[NAME_LENGHT];
}full_name;

typedef struct Employee{

    //char name[NAME_LENGHT];
    full_name name; 
    int age; //64 pensionare
    int salary;
}employee;


int main(){
    
    FILE *input=fopen("./example.txt", "r");
    if(input == NULL){
        perror("ERROR when opening file");
        exit(EXIT_FAILURE);
    }

    employee list[100];
    int i=0;

    while(fscanf(input, "%s %s %d %d\n", &list[i].name.surname, &list[i].name.first_name, &list[i].age, &list[i].salary) == 4){
        printf("%s %s %d %d\n", list[i].name.surname, list[i].name.first_name, list[i].age, list[i].salary);
        i++;
    }

    fclose(input);




    return 0;
}