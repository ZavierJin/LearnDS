/* 7-6 Root of AVL Tree */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_TREE 20 /* maximum number of nodes in a tree */
typedef int ElementType;

/* 平衡二叉搜索树AVL-Tree */
typedef struct AVLNode *Position;
typedef Position AVLTree; /* AVL树类型 */
struct AVLNode{
    ElementType Element; /* 结点数据 */
    AVLTree Left;     /* 指向左子树 */
    AVLTree Right;    /* 指向右子树 */
    int Height;       /* 树高 */
};

#define MAX(a,b) ((a>b)?(a):(b))

AVLTree build_AVLtree(int n);
AVLTree Insert(AVLTree T, ElementType X);
int GetHeight(AVLTree A);
AVLTree SingleLeftRotation ( AVLTree A );
AVLTree SingleRightRotation ( AVLTree A );
AVLTree DoubleLeftRightRotation ( AVLTree A );
AVLTree DoubleRightLeftRotation ( AVLTree A );

int main()
{
    AVLTree A = NULL;
    int n;

    scanf("%d\n", &n);
    A = build_AVLtree(n); 

    if(A != NULL) printf("%d\n", A->Element);
    else printf("NULL\n");

    return 0;
}

AVLTree build_AVLtree(int n)
{
    AVLTree A = NULL;
    ElementType num;
    int i;

    for(i=0; i<n; ++i){
        scanf("%d", &num);
        A = Insert(A, num);
    }
    return A;
}

int GetHeight(AVLTree A)
{
    if(A != NULL) return A->Height;
    else return 0;
}

AVLTree SingleLeftRotation ( AVLTree A )
{ /* 注意：A必须有一个左子结点B */
  /* 将A与B做左单旋，更新A与B的高度，返回新的根结点B */     
 
    AVLTree B = A->Left;
    A->Left = B->Right;
    B->Right = A;
    A->Height = MAX( GetHeight(A->Left), GetHeight(A->Right) ) + 1;
    B->Height = MAX( GetHeight(B->Left), A->Height ) + 1;
  
    return B;
}

AVLTree SingleRightRotation ( AVLTree A )
{
    AVLTree B = A->Right;
    A->Right = B->Left;
    B->Left = A;
    A->Height = MAX( GetHeight(A->Left), GetHeight(A->Right) ) + 1;
    B->Height = MAX( GetHeight(B->Right), A->Height ) + 1;

    return B;
}
 
AVLTree DoubleLeftRightRotation ( AVLTree A )
{ /* 注意：A必须有一个左子结点B，且B必须有一个右子结点C */
  /* 将A、B与C做两次单旋，返回新的根结点C */
     
    /* 将B与C做右单旋，C被返回 */
    A->Left = SingleRightRotation(A->Left);
    /* 将A与C做左单旋，C被返回 */
    return SingleLeftRotation(A);
}

AVLTree DoubleRightLeftRotation ( AVLTree A )
{ 
    /* 将B与C做左单旋，C被返回 */
    A->Right = SingleLeftRotation(A->Right);
    /* 将A与C做右单旋，C被返回 */
    return SingleRightRotation(A);
}

AVLTree Insert( AVLTree T, ElementType X )
{ /* 将X插入AVL树T中，并且返回调整后的AVL树 */
    if (T == NULL) { /* 若插入空树，则新建包含一个结点的树 */
        T = (AVLTree)malloc(sizeof(struct AVLNode));
        T->Element = X;
        T->Height = 0;
        T->Left = T->Right = NULL;
    } /* if (插入空树) 结束 */
 
    else if ( X < T->Element ) {
        /* 插入T的左子树 */
        T->Left = Insert( T->Left, X);
        /* 如果需要左旋 */
        if ( GetHeight(T->Left)-GetHeight(T->Right) == 2 ){
            if ( X < T->Left->Element ) 
               T = SingleLeftRotation(T);      /* 左单旋 */
            else 
               T = DoubleLeftRightRotation(T); /* 左-右双旋 */
        }
            
    } /* else if (插入左子树) 结束 */
     
    else if ( X > T->Element ) {
        /* 插入T的右子树 */
        T->Right = Insert( T->Right, X );
        /* 如果需要右旋 */
        if ( GetHeight(T->Left)-GetHeight(T->Right) == -2 ){
            if ( X > T->Right->Element ) 
               T = SingleRightRotation(T);     /* 右单旋 */
            else 
               T = DoubleRightLeftRotation(T); /* 右-左双旋 */
        }
    } /* else if (插入右子树) 结束 */

    /* else X == T->Element，无须插入 */
 
    /* 别忘了更新树高 */
    T->Height = MAX( GetHeight(T->Left), GetHeight(T->Right) ) + 1;
    return T;
}