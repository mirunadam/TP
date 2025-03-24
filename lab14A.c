// Row A. CSV files A .csv (comma separated values) file contains the grade situation for a class of students.
// Each line contains fields separated by commas. The first field is the student name (one word), followed by up to 10 fields
// with real-numbered grades or other characters; any remainder of the line is ignored.
// Give the filename from the command line arguments and read the file using an appropriate data structure; you may assume there
// are at most 200 students. Compute averages for the students that have 10 passing grades. Sort students in decreasing order of 
// their grade averages; break ties in alphabetical order. Print the sorted list with grade averages.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STUDENT_NUMBER 200
//Numarul de linii pe care le poate avea fisierul
#define MAX_NAME_SIZE  50
//Presupunem ca numele fiecarui student are maxim 50 caractere
#define MAX_GRADE_NUMBER 10
//Maxim zece note per student

struct Student{
    char student_name[MAX_NAME_SIZE];
    double grade[MAX_GRADE_NUMBER];
    double average;
};
//Structul student va tine numele, nota si media notelor

double average_calculator(double grade[], int number_of_grades){
    //calculam media aritmetica a notelor
    //count tine minte cate note sunt, result tine minte suma notelor
    //iar la final impartim result la count
    double result = 0;
    double count = 0;
    
    for (int i = 0; i < number_of_grades; i ++){
        
        if(grade[i] >= 0){
            
            result += grade[i];
            count ++;
        }
    }
    return result / count;
}

int sort_values(const void *x, const void *y){
    
    struct Student *first_student = (struct Student *)x;
    struct Student *second_student = (struct Student *)y;
    //preluam din main valorile pentru cele doua structuri pe care
    //urmeaza sa le comparam
    
    if(first_student -> average > second_student -> average){
        return -1;
        //numar pozitiv daca media primului e mai mare decat media celui de al doilea
    }
    else if(first_student -> average < second_student -> average){
        return 1;
        //negativ daca media celui de al doilea e mai mare decat media primului
    }
    else return strcmp(first_student -> student_name , second_student -> student_name);
}//daca mediile sunt egale comparam alfabetic

int main (int argc, char *argv[])
{
    FILE *file = fopen(argv[1], "r");//r inseamna reading only
    
    if(file == NULL){
        perror("Error encountered while opening the file");
        return 1;
    }
    
    struct Student students[MAX_STUDENT_NUMBER];
    
    int number_of_students = 0;
    
    while(fscanf(file, "%50[^,]", students[number_of_students].student_name) > 0){
        //fscanf citeste din file
        //formatarea %50[^,] inseamna odata ca citeste maxim 50 de caractere
        //[^,] inseamna ca o sa ignore virgulele pe care le gaseste in fisier 
        students[number_of_students].average = average_calculator(students[number_of_students].grade, MAX_GRADE_NUMBER);
        
        number_of_students ++;
        
        while(fgetc(file) != '\n');
        //asta nu face nimic doar da skip pana la linia urmatoare
    }
    fclose(file);
    
    qsort(students, number_of_students, sizeof(struct Student), sort_values);
    
    for(int i = 0; i < number_of_students; i ++){
        printf("%s , %lf", students[i].student_name, students[i].average);
    }
    return 0;
}
