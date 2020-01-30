// Stack (use array)
// need to declare the array size at the beginning
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "stack_used_array.h"


// Place in implementation file
// Stack implementation is a dynamically allocated array
#define EMPTY_TOS -1
#define MIN_STACK_SIZE 2

struct StackRecord
{
    int capacity;
    int top_of_stack;
    ElementType* array;
};

void test_stack();


// function
int is_empty(Stack s)
{
    return s->top_of_stack == EMPTY_TOS;
}

int is_full(Stack s)
{
    return s->top_of_stack == (s->capacity - 1);
}

Stack create_stack(int max_elements)
{
    Stack s = NULL;

    if(max_elements < MIN_STACK_SIZE){
        printf("Error, stack size is too small.\n");
        return NULL;
    }

    s = (Stack)malloc(sizeof(struct StackRecord));
    if(s == NULL){
        printf("Out of space!\n");
        return NULL;
    }
        
    s->array = (ElementType*)malloc(sizeof(ElementType)*max_elements);
    if(s->array == NULL){
        printf("Out of space!\n");
        return NULL;
    }

    s->capacity = max_elements;
    make_empty(s);

    return s;
}

void dispose_stack(Stack s)
{
    if(s != NULL){
        free(s->array);
        free(s);
    }
}

void make_empty(Stack s)
{
    s->top_of_stack = EMPTY_TOS;
}

void push(ElementType x, Stack s)
{
    if(!is_full(s)){
        s->top_of_stack += 1;
        s->array[s->top_of_stack] = x;
    }else
        printf("Full Stack!\n");
}

ElementType top(Stack s)
{
    if(!is_empty(s))
        return s->array[s->top_of_stack];
    else{
        printf("Error, empty stack1!\n");
        return 0;
    }
}

void pop(Stack s)
{
    if(!is_empty(s))
        s->top_of_stack -= 1;
    else
        printf("Error, empty stack2!\n");
}

ElementType top_and_pop(Stack s)
{
    if(!is_empty(s)){
        s->top_of_stack -= 1;
        return s->array[s->top_of_stack + 1];
    }else{
        printf("Error, empty stack3!\n");
        return 0;
    }
}

void test_stack()
{
    Stack s = NULL;
    int arr[] = {3, 4, 5, 6, 7, 8};
    int n = 6;
    int i;
    ElementType tmp;

    s = create_stack(n);
    if(s == NULL){
        printf("ERROR!\n");
        return;
    }

    for(i = 0; i < n && !is_full(s); i++){
        printf("%4d", arr[i]);
        push(arr[i], s);
    }
    printf("\n");

    for(i = 0; i < n && !is_empty(s); i++){
        tmp = top_and_pop(s);
        printf("%4d", tmp);
    }
    printf("\n");
}
