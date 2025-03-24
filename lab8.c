#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//THIS IS FOR EXAM CSV FILE WITH PARSING LINKED LIST
//look at (from lect linked lists)
//pg 55 - add to front, 
//28 -for the create node
// 40 - print list
//72 - add to back
// 108 - adding a node to an ordered list
#define MAX 100
#define MAX_LINE_SIZE 256

typedef struct _movies{
    unsigned int ryear;
    char title[MAX];
    char buget[MAX];
    struct _movies *next;
} movie;

movie *head, *tail, *crt;

void init_list(movie **head, movie **tail){
    *head = *tail = NULL;
}

movie *create_node(unsigned int ryear, char title[], char buget[]){
    movie *p; //movie will be our node
    p = (movie *) malloc(sizeof(movie));

    if(p == NULL){
        printf("ERROR at memory allocation\n");
        exit(1);
    }
    p->ryear = ryear;
    strcpy(p->title, title);
    strcpy(p->buget, buget);

    p->next = NULL;
    return p;

}
void print_list(movie *head){
    movie *p;

    if(head == NULL){
        printf("The list is empty\n");
    }
    else{
        p = head;
        while(p){
            printf("%d, ", p->ryear);
            printf("%s, ", p->title);
            printf("%s\n", p->buget);
            p = p->next;
        }
        printf("\n");
    }
}

void add_to_front(movie *movie_to_add, movie **head, movie **tail){

    movie_to_add->next = *head;

    if(*head == NULL){
        *tail = movie_to_add;
    }
    *head = movie_to_add;
}

void add_to_back(movie *movie_to_add, movie **head, movie **tail){
    if(*tail == NULL){
        *head = movie_to_add;
    }
    else{
        (*tail)->next = movie_to_add;
    }
    *tail = movie_to_add;
    movie_to_add->next = NULL;
}

void add_ordered(movie *movie_to_add, movie **head, movie **tail){
    if((!*head)||(movie_to_add->ryear <= (*head)->ryear)){
         if (!*head || (movie_to_add->ryear < (*head)->ryear) || ((movie_to_add->ryear == (*head)->ryear) && strcmp(movie_to_add->title, (*head)->title) < 0)) {
            // Add to front if the list is empty or the new movie's release year is earlier or if they have the same release year but the new movie's title is lexicographically earlier
            add_to_front(movie_to_add, head, tail);
        } else {
            // If release years are equal and new movie's title should come later, insert after the head
            add_to_back(movie_to_add, head, tail);
        }
    }
    else if(movie_to_add->ryear >= (*tail)->ryear){
        add_to_back(movie_to_add, head, tail);
    }
    else{
        movie *before, *after;

        before = NULL;
        after = *head;

        while(after -> ryear < movie_to_add -> ryear){
            before = after;
            after = after->next;
        }
        before->next = movie_to_add;
        movie_to_add ->next = after;

    }
}

void parse_csv(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    char line[MAX_LINE_SIZE];
    fgets(line, MAX_LINE_SIZE, file); // Skip header line

    while (fgets(line, MAX_LINE_SIZE, file) != NULL) {
        unsigned int ryear;
        char title[MAX];
        char buget[MAX];

        char *token;
        token = strtok(line, ",");
        ryear = atoi(token);

        token = strtok(NULL, ",");
        token = strtok(NULL, ",");
        strcpy(title, token);

        int count = 0;
        while(count <3){
            token = strtok(NULL, ",");
            count++;
        }

        token = strtok(NULL, ",");
        strcpy(buget, token);


        movie *new_movie = create_node(ryear, title, buget);
        add_ordered(new_movie, &head, &tail);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    init_list(&head, &tail);
    parse_csv(argv[1]);
    print_list(head);


    movie *current = head;
    while (current != NULL) {
        movie *next = current->next;
        free(current);
        current = next;
    }

    return 0;
}
//gcc -Wall -o lab8 lab8.c
//./lab8 movies.csv