/* 7-5 Tree Traversals Again */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_TREE 30 /* maximum number of nodes in a tree */
typedef int ElementType;

typedef struct TreeNode *Tree;
struct TreeNode {
    ElementType Element;
    Tree  Left;
    Tree  Right;
};


int input[2*MAX_TREE];
int output[MAX_TREE];
int n = 0;
int node_id = 0;
int out_id = 0;


int get_input();
int BuildTree(Tree* Ptr_T); 
void PostorderTraversal( Tree T );


int main()
{
    Tree T = NULL;
    int i;

    get_input();
    BuildTree(&T); 
    PostorderTraversal(T);
    for(i=0; i<n-1; ++i)
        printf("%d ", output[i]);
    printf("%d", output[i]);

    return 0;
}

int get_input()
{
    int i, j, num;
    char ch;

    scanf("%d\n", &n);
    
    for(i=0; i<2*n; i++){
        j = 0;
        while((ch=getchar())!=' ' && ch!='\n')
            j++;
        if(j == 4){
            scanf("%d\n", &num);
            input[node_id++] = num;
        }else if(j == 3){
            input[node_id++] = -1;
        }else{
            printf("ERROR\n");
            return 0;
        }
    }
    // printf("input ok!\n");
    // if(2*n == node_id){
    //     for(i=0; i<2*n; ++i) printf("(%d, %d)", i, input[i]);
    // }else
    //     printf("node_id = %d\n", node_id);
    // printf("********************\n");
    node_id = 0;

    return 1;
}

int BuildTree(Tree* Ptr_T)
{
    int x = -1;
    x = input[node_id];

    if(node_id >= 2*n){
        // printf("ok, node_id = %d, n = %d\n", node_id, n);
        *Ptr_T = NULL;
        return 1;
    }
    if(x == -1){
        // printf("x=-1, node_id = %d\n", node_id);
        *Ptr_T = NULL;
        return 0;
    }else{
        *Ptr_T = (Tree)malloc(sizeof(struct TreeNode));
        (*Ptr_T)->Element = x;
        // printf("### x=%d, node_id = %d\n", x, node_id);
        node_id++;
        BuildTree(&((*Ptr_T)->Left));
        node_id++;
        BuildTree(&((*Ptr_T)->Right));
        return 1;
    }
}

void PostorderTraversal( Tree T )
{
    if( T ) {
        PostorderTraversal( T->Left );
        PostorderTraversal( T->Right );
        output[out_id++] = T->Element; 
    }
}

