// Queue (use circular array)
// need to declare the array size at the beginning
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


#ifndef _QUEUE_H
    #define _QUEUE_H 
    
    struct QueueRecord;
    typedef struct QueueRecord* Queue;
    typedef int ElementType;

    int is_empty(Queue q);
    int is_full(Queue q);
    Queue create_queue(int max_elements);
    void dispose_queue(Queue q);
    void make_empty(Queue q);
    void en_queue(ElementType x, Queue q);
    ElementType front(Queue q);
    void de_queue(Queue q);
    ElementType front_and_de(Queue q);
#endif  /* _QUEUE_H */


// Place in implementation file
// Queue implementation is a dynamically allocated array
#define MIN_QUEUE_SIZE 2

struct QueueRecord
{
    int capacity;
    int front;
    int rear;
    int size;
    ElementType* array;
};


// function
int is_empty(Queue q)
{
    return q->size == 0;
}

int is_full(Queue q)
{
    return q->size >= q->capacity;
}

Queue create_queue(int max_elements)
{
    Queue q = NULL;

    if(max_elements < MIN_QUEUE_SIZE){
        printf("Error, queue size is too small.\n");
        return NULL;
    }

    q = (Queue)malloc(sizeof(struct QueueRecord));
    if(q == NULL){
        printf("Out of space!\n");
        return NULL;
    }
        
    q->array = (ElementType*)malloc(sizeof(ElementType)*max_elements);
    if(q->array == NULL){
        printf("Out of space!\n");
        return NULL;
    }

    q->capacity = max_elements;
    make_empty(q);

    return q;
}

void dispose_queue(Queue q)
{
    if(q != NULL){
        free(q->array);
        free(q);
    }
}

void make_empty(Queue q)
{
    q->size = 0;
    q->front = 1;
    q->rear = 0;    //?
}

// circulate index
static int succ(int index, Queue q)
{
    index++;
    if(index == q->capacity)
        index = 0;
    return index;
}

void en_queue(ElementType x, Queue q)
{
    if(!is_full(q)){
        q->size++;
        q->rear = succ(q->rear, q);
        q->array[q->rear] = x;
    }else
        printf("Full queue!\n");
}

ElementType front(Queue q)
{
    if(!is_empty(q))
        return q->array[q->front];
    else{
        printf("Empty queue!\n");
        return 0;
    }
}

void de_queue(Queue q)
{
    if(!is_empty(q)){
        q->size--;
        q->front = succ(q->front, q);
    }else
        printf("Empty queue!\n");
}

ElementType front_and_de(Queue q)
{
    ElementType pre_front;
    if(!is_empty(q)){
        pre_front = q->front;
        q->size--;
        q->front = succ(q->front, q);
        return q->array[pre_front];
    }else{
        printf("Empty queue!\n");
        return 0;
    }
}

void test_queue()
{
    Queue q = NULL;
    int arr[] = {3, 4, 5, 6, 7, 8};
    int n = 6;
    int i;
    ElementType tmp;

    q = create_queue(n);
    if(q == NULL){
        printf("ERROR!\n");
        return;
    }

    for(i = 0; i < n && !is_full(q); i++){
        printf("%4d", arr[i]);
        en_queue(arr[i], q);
    }
    printf("\n");

    for(i = 0; i < n && !is_empty(q); i++){
        tmp = front_and_de(q);
        printf("%4d", tmp);
    }
    printf("\n");

}

int main(void)
{
    test_queue();
    return 0;
}
