#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ElementType int
#define ERROR 1e5
typedef enum { push, pop, inject, eject, end } Operation;

typedef struct Node *PtrToNode;
struct Node {
    ElementType Element;
    PtrToNode Next, Last;
};
typedef struct DequeRecord *Deque;
struct DequeRecord {
    PtrToNode Front, Rear;
};
Deque CreateDeque();
int Push( ElementType X, Deque D );
ElementType Pop( Deque D );
int Inject( ElementType X, Deque D );
ElementType Eject( Deque D );

Operation GetOp();          /* details omitted */
void PrintDeque( Deque D ); /* details omitted */

int main()
{
    ElementType X;
    Deque D;
    int done = 0;

    D = CreateDeque();
    while (!done) {
        switch(GetOp()) {
        case push: 
            scanf("%d", &X);
            if (!Push(X, D)) printf("Memory is Full!\n");
            PrintDeque(D);
            break;
        case pop:
            X = Pop(D);
            if ( X==ERROR ) printf("Deque is Empty!\n");
            else{
                printf("**Pop: %d**\n", X);
                PrintDeque(D);
            }
            break;
        case inject: 
            scanf("%d", &X);
            if (!Inject(X, D)) printf("Memory is Full!\n");
            PrintDeque(D);
            break;
        case eject:
            X = Eject(D);
            if ( X==ERROR ) printf("Deque is Empty!\n");
            else{
                printf("**Eject: %d**\n", X);
                PrintDeque(D);
            }
            break;
        case end:
            PrintDeque(D);
            done = 1;
            break;
        }
    }
    return 0;
}

/* Your function will be put here */
Deque CreateDeque()
{
    Deque D = NULL;

    D = (Deque)malloc(sizeof(struct DequeRecord));
    D->Front = (PtrToNode)malloc(sizeof(struct Node));
    D->Front->Next = NULL;
    D->Front->Last = NULL;
    D->Rear = D->Front;

    return D;  
}
int Push( ElementType X, Deque D )
{
    PtrToNode P = NULL;

    // if(D == NULL) return 0;

    P = (PtrToNode)malloc(sizeof(struct Node));
    P->Element = X;
    P->Next = D->Front->Next;
    if(P->Next == NULL) 
        D->Rear = P;
    else 
        P->Next->Last = P;
    P->Last = D->Front;
    D->Front->Next = P;
    return 1;
}
ElementType Pop( Deque D )
{
    ElementType res;
    PtrToNode P = NULL;

    // if(D == NULL) return ERROR;
    if(D->Front == D->Rear){
        return ERROR;
    }
    P = D->Front->Next;
    res = P->Element;
    D->Front->Next = P->Next;
    if(P->Next != NULL) 
        P->Next->Last = D->Front;
    else
        D->Rear = D->Front; 
    free(P);
    return res;
}
int Inject( ElementType X, Deque D )
{
    PtrToNode P = NULL;

    // if(D == NULL) return 0;

    P = (PtrToNode)malloc(sizeof(struct Node));
    P->Element = X;
    P->Next = NULL;
    P->Last = D->Rear;
    D->Rear->Next = P;
    D->Rear = P;

    return 1;
}
ElementType Eject( Deque D )
{
    ElementType res;
    PtrToNode P = NULL;

    // if(D == NULL) return ERROR;
    if(D->Front == D->Rear){
        return ERROR;
    }
    P = D->Rear;
    res = P->Element;
    D->Rear = P->Last;
    if(P->Last != NULL) 
        P->Last->Next = NULL;
    free(P);
    return res;
}




Operation GetOp()
{
    Operation op = end;
    char text[10];
    scanf("%s",text);
    // puts(text);

    if(!strcmp(text, "Push")) op = push;
    else if(!strcmp(text, "Pop")) op = pop;
    else if(!strcmp(text, "Inject")) op = inject;
    else if(!strcmp(text, "Eject")) op = eject;
    else if(!strcmp(text, "End")) op = end;

    // printf("operation: %d\n", op);
    return op;
}

void PrintDeque( Deque D )
{
    PtrToNode P = NULL;

    printf("**Inside:");
    for(P=D->Front->Next; P!=NULL; P=P->Next){
        printf("%2d",P->Element);
    }
    printf("**\n");
}



