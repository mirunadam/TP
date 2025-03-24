#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct _movies{
    unsigned int ryear;
    char *title;
    char *budget;
    struct _movies *next;
}movie;

movie *head,*tail,*crt;


void init_list(movie **head,movie **tail)
{
    *head=*tail=NULL;
}

movie *create_node(int ryear, char *title, char *budget)
{
    movie *p;
    p=(movie *)malloc(sizeof(movie));

    if(p==NULL)
    {
        perror("Memory was not allocated correctly");
        exit(EXIT_FAILURE);
    }
    p->ryear=ryear;
    strcpy(p->title,title);
    strcpy(p->budget,budget);
    p->next=NULL;
    return p;
}


void print_list(movie *head)
{
    movie *p;
    if(NULL==head)
    {
        printf("the list is empty\n");
    }
    else
    {
        p=head;
        while(p)
        {
            printf("The release year is %d\n",p->ryear);
            printf("The title is %s\n",p->title);
            printf("The budget is %s\n",p->budget);
            p=p->next;
        }
        printf("\n");
    }
}


void add_to_front(movie *movie_to_add,movie **head,movie **tail)
{
    movie_to_add->next=*head;
    if(NULL==*head)
    {
        *tail=movie_to_add;
    }
    *head=movie_to_add;
}

void add_to_back(movie *movie_to_add,movie **head,movie **tail)
{
    if(*tail==NULL)
    {
        *head=movie_to_add;
    }
    else{
        (*tail)->next=movie_to_add;
    }
    *tail=movie_to_add;
    movie_to_add->next=NULL;
}

void add_ordered(movie *movie_to_add,movie **head,movie **tail)
{
    if((!*head) || (movie_to_add->ryear<=(*head)->ryear))
    {
        add_to_front(movie_to_add,head,tail);
    }
    else if(movie_to_add->ryear >= (*tail)->ryear){ ///thissss
        add_to_back(movie_to_add, head, tail);
    }
    else{
        movie *before,*after;
        
        before=NULL;
        after=*head;

        while(after->ryear<movie_to_add->ryear)
        {
            before=after;
            after=after->next;
        }
        before->next=movie_to_add;
        movie_to_add->next=after;
    }
}





int main()
{
    movie *a=create_node(1989,"Star Wars","11100000");
    movie *b=create_node(2019,"Little Women","12000000");
    movie *c=create_node(2023,"Poor Things","23000000");

    init_list(&head,&tail);

    add_ordered(a,&head,&tail);
    add_ordered(c,&head,&tail);
    add_ordered(b,&head,&tail);

    print_list(head);
    return 0;

}