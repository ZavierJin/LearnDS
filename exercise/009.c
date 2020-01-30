/* 7-20 Binary Search Tree */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 10
#define MAX_TEST 1000
typedef int ElementType;
typedef struct BSNode *BinTree;
struct BSNode{
    ElementType Data; /* 结点数据 */
    BinTree Left;     /* 指向左子树 */
    BinTree Right;    /* 指向右子树 */
    int Tag;          /* 0为未被找过 */
};

BinTree Insert( BinTree BST, ElementType X );
BinTree build_tree( int N ); 
void renew_tree( BinTree BST);
void free_tree( BinTree BST);
void check( BinTree BST, int N );
bool search( BinTree BST, ElementType X );
void show_output();

int output[MAX_TEST];
int output_id = 0;

int main(void)
{
    int N, L, i;
    BinTree BST = NULL;
    while( scanf("%d", &N)==1 && N!=0 ){
        scanf("%d", &L);
        BST = build_tree(N);
        for( i = 0; i < L; ++i ){
            renew_tree(BST);
            check(BST, N);
        }    
    }
    show_output();

    return 0;
}

void show_output()
{
    int i;
    for(i=0; i<output_id; ++i){
        if( output[i] )
            printf("Yes\n");
        else
            printf("No\n");
    }
}

bool search( BinTree BST, ElementType X )
{
    bool is_same = false;
    BinTree tmp = BST;
    while( tmp ){
        if( X == tmp->Data && tmp->Tag==0 ){
            tmp->Tag = 1;
            is_same = true;
            break;
        }else if( X != tmp->Data && tmp->Tag == 1){
            if( X < tmp->Data){
                tmp = tmp->Left;
            }else{
                tmp = tmp->Right;
            }
        }else{
            is_same = false;
            break;
        }
    }
    
    return is_same;
}

void check( BinTree BST, int N )
{
    int i, x;
    bool is_same = true;
    for(i=0; i<N; ++i){
        scanf("%d", &x);
        if(!search(BST, x)) {
            is_same = false;
        }
    }
    output[output_id++] = is_same ? 1 : 0;

    return;
}

BinTree build_tree( int N )
{
    BinTree BST = NULL;
    int i, x;

    for(i=0; i<N; ++i){
        scanf("%d", &x);
        BST = Insert(BST, x);
    }
    return BST;
}

void free_tree( BinTree BST)
{
    if( BST ){
        free_tree(BST->Left);
        free_tree(BST->Right);
        free(BST);
    }
    return;
}

void renew_tree( BinTree BST)
{
    if( BST ){
        BST->Tag = 0;
        renew_tree(BST->Left);
        renew_tree(BST->Right);
    }
    return;
}


/* 二叉搜索树 */
BinTree Insert( BinTree BST, ElementType X )
{
    if( !BST ){ /* 若原树为空，生成并返回一个结点的二叉搜索树 */
        BST = (BinTree)malloc(sizeof(struct BSNode));
        BST->Data = X;
        BST->Left = BST->Right = NULL;
    }
    else { /* 开始找要插入元素的位置 */
        if( X < BST->Data )
            BST->Left = Insert( BST->Left, X );   /*递归插入左子树*/
        else  if( X > BST->Data )
            BST->Right = Insert( BST->Right, X ); /*递归插入右子树*/
        /* else X已经存在，什么都不做 */
    }
    return BST;
}