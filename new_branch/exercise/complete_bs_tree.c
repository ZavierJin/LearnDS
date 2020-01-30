/* 7-7 Complete Binary Search Tree */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MaxTree 1000 /* maximum number of nodes in a tree */
typedef int ElementType;

typedef struct TreeNode *Tree;
struct TreeNode {
    ElementType Element;
    Tree  Left;
    Tree  Right;
    int Depth;
};
int input[MaxTree];
int input_id = 0;
int output[MaxTree];
int output_id = 0;
int max_depth = 0;
int bottom_id = 0;

Tree BuildTree(int N);
void insert(Tree T);
void show_res();
void Level_order ( Tree T);

int cmp ( const void *a , const void *b){
    return *(int *)a - *(int *)b;
}


int main()
{
    Tree T = NULL;
    int n;

    scanf("%d\n", &n);
    T = BuildTree(n);
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


Tree new_node(int depth)
{
    Tree T = (Tree)malloc(sizeof(struct TreeNode));
    T->Element = -1;
    T->Left = T->Right = NULL;
    T->Depth = depth;
    return T;
}

void insert(Tree T)
{
    bool bot_is_full = false;
    if(T->Depth == max_depth && bottom_id > 0){
        T->Element = input[input_id++];
        bottom_id--;
    }else{
        bot_is_full = (T->Depth == max_depth-1 && bottom_id <= 0);
        if(!bot_is_full){
            T->Left = new_node(T->Depth + 1);
            insert(T->Left);
        }
        T->Element = input[input_id++];
        bot_is_full = (T->Depth == max_depth-1 && bottom_id <= 0);
        if(!bot_is_full){
            T->Right = new_node(T->Depth + 1);
            insert(T->Right);
        }
    }

    return ;
}

Tree BuildTree(int N)
{
    Tree T = NULL;
    int i;

    for(i=0; i<N; ++i)
        scanf("%d", &input[i]);
    qsort(input, N, sizeof(input[0]), cmp);

    for(i=0; i<=N; ++i){
        if(pow(2, i)-1 >= N){
            max_depth = i - 1;
            bottom_id = N - (pow(2, i-1)-1);
            break;
        }
    }
    // printf("max:%d, bo:%d\n", max_depth, bottom_id);
    T = new_node(0);
    insert(T);

    return T;
}


// 队列数组实现
#ifndef ERROR
#define ERROR NULL
#endif
typedef int Position;
typedef Tree ElementType_2;
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

void Level_order ( Tree T)
{
    Queue Q = NULL;
    Tree tmp = NULL;
    int MaxSize = 1000;

    Q = CreateQueue(MaxSize);

    if(T != NULL) AddQ(Q, T);
    while(!IsEmpty(Q)){
        tmp = DeleteQ(Q);
        output[output_id++] = tmp->Element;
        if(tmp->Left != NULL) AddQ(Q, tmp->Left);
        if(tmp->Right != NULL) AddQ(Q, tmp->Right);
    }
}