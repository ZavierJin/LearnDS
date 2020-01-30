/* 7-7 Complete Binary Search Tree */
/* solution_2 #using arr# */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MaxTree 1000 /* maximum number of nodes in a tree */
typedef int ElementType;

typedef struct CBSTreeNode *CBSTree;
struct CBSTreeNode {
    ElementType* Element;
    int max_size;
};
int input[MaxTree];
int input_id = 0;
int output[MaxTree];
int output_id = 0;

CBSTree BuildCBSTree(int N);
void insert(CBSTree T, int i);
void show_res();
void Level_order ( CBSTree T);

int cmp ( const void *a , const void *b){
    return *(int *)a - *(int *)b;
}


int main()
{
    CBSTree T = NULL;
    int n;

    scanf("%d\n", &n);
    T = BuildCBSTree(n);
    Level_order(T);
    show_res();
    return 0;
}

void show_res()
{
    int i;
    for(i=0; i<output_id-1; ++i)
        printf("%d ", output[i]);
    printf("%d", output[i]);
}

void insert(CBSTree T, int i)
{
    if(2*i <= T->max_size) insert(T, 2*i);
    T->Element[i] = input[input_id++];
    if(2*i+1 <= T->max_size) insert(T, 2*i+1);

    return ;
}

CBSTree BuildCBSTree(int N)
{
    CBSTree T = NULL;
    int i;

    for(i=0; i<N; ++i)
        scanf("%d", &input[i]);
    qsort(input, N, sizeof(input[0]), cmp);

    T = (CBSTree)malloc(sizeof(struct CBSTreeNode));
    T->Element = (ElementType*)malloc((N+1) * sizeof(ElementType));
    T->max_size = N;
    T->Element[0] = 2000;   // 哨兵，这题没用

    insert(T, 1);

    return T;
}


// 队列数组实现
#ifndef ERROR
#define ERROR -1
#endif
typedef int Position;
typedef int ElementType_2;
struct QNode {
    ElementType_2 *Data;     /* 存储元素的数组 */
    Position Front, Rear;  /* 队列的头、尾指针 */
    int MaxSize;           /* 队列最大容量 */
};
typedef struct QNode *Queue;
 
Queue CreateQueue( int MaxSize )
{
    Queue Q = (Queue)malloc(sizeof(struct QNode));
    Q->Data = (ElementType_2 *)malloc(MaxSize * sizeof(ElementType_2));
    Q->Front = Q->Rear = 0;
    Q->MaxSize = MaxSize;
    return Q;
}
 
bool IsFull( Queue Q )
{
    return ((Q->Rear+1)%Q->MaxSize == Q->Front);
}
 
bool AddQ( Queue Q, ElementType_2 X )
{
    if ( IsFull(Q) ) {
        return false;
    }
    else {
        Q->Rear = (Q->Rear+1)%Q->MaxSize;
        Q->Data[Q->Rear] = X;
        return true;
    }
}
 
bool IsEmpty( Queue Q )
{
    return (Q->Front == Q->Rear);
}
 
ElementType_2 DeleteQ( Queue Q )
{
    if ( IsEmpty(Q) ) { 
        return ERROR;
    }
    else  {
        Q->Front =(Q->Front+1)%Q->MaxSize;
        return  Q->Data[Q->Front];
    }
}

void Level_order ( CBSTree T)
{
    Queue Q = NULL;
    int MaxSize = 1000;
    int index = 0;

    Q = CreateQueue(MaxSize);

    if(T->max_size > 0) AddQ(Q, 1);
    while(!IsEmpty(Q)){
        index = DeleteQ(Q);
        output[output_id++] = T->Element[index];
        if(2*index <= T->max_size) AddQ(Q, 2*index);
        if(2*index+1 <= T->max_size) AddQ(Q, 2*index+1);
    }
}