// Tree
// no limit for children number
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


#ifndef _TREE_H
    #define _TREE_H 
    
    struct TreeNode;
    typedef struct TreeNode* Tree;
    typedef int ElementType;

#endif  /* _TREE_H */


// Place in implementation file

struct TreeNode
{
    ElementType element;
    Tree        first_child;
    Tree        next_sibling;
};


int main(void)
{
    return 0;
}
