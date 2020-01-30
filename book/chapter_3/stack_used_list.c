// Stack (use Singly linked list)
// malloc and free are expensive
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


#ifndef _STACK_H
#define _STACK_H 

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode Stack;
typedef int ElementType;

int is_empty(Stack s);
Stack create_stack(void);
// void dispose_stack(Stack s);
void make_empty(Stack s);
void push(ElementType x, Stack s);
ElementType top(Stack s);
void pop(Stack s);

#endif  /* _STACK_H */

// Place in implementation file
// Stack implementation is a linked list with a header
struct Node
{
    ElementType element;
    PtrToNode   next;
};

// function
int is_empty(Stack s)
{
    return s->next == NULL;
}

Stack create_stack(void)
{
    Stack s = NULL;

    s = (PtrToNode)malloc(sizeof(struct Node));  // header
    if(s == NULL)
        printf("Out of space!!!\n");
    else{
        s->next = NULL;
        make_empty(s);
    }

    return s;
}

void make_empty(Stack s)
{
    if(s == NULL)
        printf("Must use create_stack first\n");
    else
        while(!is_empty(s))
            pop(s);
}

void push(ElementType x, Stack s)
{
    PtrToNode tmp_cell = NULL;

    tmp_cell = (PtrToNode)malloc(sizeof(struct Node));
    if(tmp_cell == NULL) 
        printf("Out of space!!!\n");
    else{
        tmp_cell->element = x;
        tmp_cell->next = s->next;
        s->next = tmp_cell;
    }
}

ElementType Top(Stack s)
{
    if(!is_empty(s))
        return s->next->element;
    else
        printf("Empty Stack");
    return 0;   // return value used to avoid warning
}

void pop(Stack s)
{
    PtrToNode first_cell = NULL;

    if(!is_empty(s)){
        first_cell = s->next;
        s->next = s->next->next;
        free(first_cell);
    }
}

int main()
{
    return 0;
}