/* 层序打印树叶 */
#include <stdio.h>
#include <stdlib.h>

#define MaxTree 10 /* maximum number of nodes in a tree */
// typedef int ElementType;
#define Null -1

// typedef struct TreeNode *Tree;
struct TreeNode {
    // ElementType Element;
    int  Left;
    int  Right;
}My_Tree[MaxTree];
int root_id = -1;

void BuildTree(); 

int search_leaves (int output[]);

int main()
{
    int total_leaves = 0;
    int output[MaxTree];
    int i;

    BuildTree();
    total_leaves = search_leaves(output);

    for(i=0; i<total_leaves-1; ++i)
        printf("%d ", output[i]);
    printf("%d\n", output[i]);
    return 0;
}

/* Your function will be put here */
void BuildTree()
{
    int n;
    int left_index, right_index;
    char lc, rc;
    int check[MaxTree];

    scanf("%d", &n);
    for(int i=0; i<n; ++i) check[i] = 0;
    for(int i=0; i<n; ++i){
        getchar();
        scanf("%c %c", &lc, &rc);
        if(lc != '-'){
            left_index = lc - '0';
            My_Tree[i].Left = left_index;
            check[left_index] = 1;
        }else
            My_Tree[i].Left = Null;
        if(rc != '-'){
            right_index = rc - '0';
            My_Tree[i].Right = right_index;
            check[right_index] = 1;
        }else
            My_Tree[i].Right = Null;
    }
    for(int i=0; i<n; ++i){
        if(!check[i]){
            root_id = i;
            break;
        }
    }
    // for(int i=0; i<n; ++i){
    //     printf("%d##%d,%d\n", i, My_Tree[i].Left, My_Tree[i].Right);
    // }
    // printf("root_id: %d\n", root_id);
}




// 队列数组实现
#include <stdbool.h>
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

int search_leaves (int output[])
{
    Queue Q = NULL;
    int tmp_id = Null;
    int MaxSize = 10;
    int is_leaf = -1;
    int total_leaves = 0;

    Q = CreateQueue(MaxSize);

    AddQ(Q, root_id);
    while(!IsEmpty(Q)){
        is_leaf = -1;
        
        tmp_id = DeleteQ(Q);
        if(My_Tree[tmp_id].Left != Null) AddQ(Q, My_Tree[tmp_id].Left);
        else is_leaf++;
        if(My_Tree[tmp_id].Right != Null) AddQ(Q, My_Tree[tmp_id].Right);
        else is_leaf++;

        if(is_leaf == 1)
            output[total_leaves++] = tmp_id;
    }
    return total_leaves;
}