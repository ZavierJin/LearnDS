// Binary Search Tree
// assume that all numbers are different
// assume that elements in left tree is small

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


#ifndef _TREE_H
    #define _TREE_H 
    
    struct TreeNode;
    typedef struct TreeNode* Position;
    typedef struct TreeNode* SearchTree;
    typedef int ElementType;

    SearchTree make_empty(SearchTree t);
    Position find(ElementType x, SearchTree t);
    Position find_min(SearchTree t);
    Position find_max(SearchTree t);
    SearchTree insert(ElementType x, SearchTree t);
    SearchTree delete(ElementType x, SearchTree t);
    ElementType retrieve(Position p);

#endif  /* _TREE_H */


// Place in implementation file

struct TreeNode
{
    ElementType element;
    SearchTree  left;
    SearchTree  right;
};

// functions

SearchTree make_empty(SearchTree t)
{
    if (t != NULL)
    {
        make_empty(t->left);
        make_empty(t->right);
        free(t);
    }
}

Position find(ElementType x, SearchTree t)
{
    if(t == NULL)
        return NULL;

    if(x < t->element)
        return find(x, t->left);
    else if(x > t->element)
        return find(x, t->right);
    else 
        return t;
}

/*
// use recursion
Position find_min(SearchTree t)
{
    if(t == NULL)
        return NULL;

    if(t->left != NULL)
        return find_min(t->left);
    else
        return t;
}   
*/

// not use recursion
Position find_min(SearchTree t)
{
    if(t == NULL)
        return NULL;

    while(t->left != NULL)
        t = t->left;    // t is a copy, a formal parameter
    return t;
}

Position find_max(SearchTree t)
{
    if(t == NULL)
        return NULL;

    while(t->right != NULL)
        t = t->right;    // t is a copy, a formal parameter
    return t;
}

SearchTree insert(ElementType x, SearchTree t)
{
    if(t == NULL){
        // Create and return a one-node tree
        t = malloc(sizeof(struct TreeNode));
        if(t == NULL)
            printf("Out of space!\n");
        else{
            t->element = x;
            t->left = t->right = NULL;
        }
    }else{
        if(x < t->element)
            t->left = insert(x, t->left);
        else(x > t->element)
            t->right = insert(x, t->right);
        // else x is in the tree already, we'll do nothing
    }
    return t;   // do not forget this line!!
}

SearchTree delete(ElementType x, SearchTree t)
{
    Position tmp_cell = NULL;

    if(t == NULL){
        printf("Element not found.\n");
        return NULL;
    }

    if(x < t->element){     // go left
        t->left = delete(x, t->left);
    }else if(x > t->element){   // go right
        t->right = delete(x, t->right);
    }else{  // found element to be deleted
        if(t->left && t->right){    // two children
            // replace with smallest in right subtree
            tmp_cell = find_min(t->right);
            t->element = tmp_cell->element;
            t->right = delete(t->element, t->right);
        }else{  // one or zero child
            tmp_cell = t;
            if(t->left == NULL)
                t = t->right;
            else if(t->right == NULL)
                t = t->left;
            free(tmp_cell);
        }
    }
    return t;
    // optimize: 
    // write a delete_min function to enhance efficiency
    // or, use lazy delection
}



int main(void)
{
    return 0;
}
