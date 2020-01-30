// AVL Tree
// The left and right subtrees of each node differ by 1
// assume that all numbers are different
// assume that elements in left tree is small

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX(a,b) ((a>b)?a:b)


#ifndef _AVL_TREE_H
    #define _AVL_TREE_H 
    
    struct AvlNode;
    typedef struct AvlNode* Position;
    typedef struct AvlNode* AvlTree;
    typedef int ElementType;

    AvlTree make_empty(AvlTree t);
    Position find(ElementType x, AvlTree t);
    Position find_min(AvlTree t);
    Position find_max(AvlTree t);
    AvlTree insert(ElementType x, AvlTree t);
    AvlTree delete(ElementType x, AvlTree t);
    ElementType retrieve(Position p);

#endif  /* _AVL_TREE_H */


// Place in implementation file

struct AvlNode
{
    ElementType element;
    AvlTree     left;
    AvlTree     right;
    int         height;
};


// functions


// return height of a subtree
static int tree_h(Position p)
{
    if(p == NULL)
        return -1;
    else 
        return p->height;
}

static void update_h(Position p)
{
    if(p != NULL){
        p->height = MAX(tree_h(p->left), tree_h(p->right)) + 1;
    }
}

// rotation function

// This function can be called only if k2 has a left child
// Perform a rotate between a node (k2) and its left child
// Update heights, then return new root
static Position single_rot_with_left(Position k2)
{
    Position k1;

    k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;

    update_h(k2);
    update_h(k1);

    return k1;  // new root
}
// right
static Position single_rot_with_right(Position k2)
{
    Position k1;

    k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;

    update_h(k2);
    update_h(k1);

    return k1;  // new root
}

// This function can be called only if k3 has a left 
// child and k3's left child has a right child
// Do the left-right double rotation
// Update heights, then return new root
static Position double_rot_with_left(Position k3)
{
    // Rotate between k1 and k2 (k1's right child)
    k3->left = single_rot_with_right(k3->right);

    // Rotate between k2 and k3
    return single_rot_with_left(k3);
}
// right
static Position double_rot_with_right(Position k3)
{
    // Rotate between k1 and k2 (k1's left child)
    k3->right = single_rot_with_left(k3->left);

    // Rotate between k2 and k3
    return single_rot_with_right(k3);
}

// AVL_Insert

AvlTree insert(ElementType x, AvlTree t)
{
    if(t == NULL){
        // Create and return a one-node tree
        t = malloc(sizeof(struct AvlNode));
        if(t == NULL)
            printf("Out of space!\n");
        else{
            t->element = x; t->height = 0;
            t->left = t->right = NULL;
        }
    }else{
        if(x < t->element){
            t->left = insert(x, t->left);
            if(tree_h(t->left) - tree_h(t->right) == 2){
                // Judge which side was previously inserted
                if(x < t->left->element)    
                    t = single_rot_with_left(t);
                else
                    t = double_rot_with_left(t);
            }
        }
        else if(x > t->element){
            t->right = insert(x, t->right);
            if(tree_h(t->right) - tree_h(t->left) == 2){
                // Judge which side was previously inserted
                if(x > t->right->element)
                    t = single_rot_with_right(t);
                else
                    t = double_rot_with_right(t);
            }
        }

        // else x is in the tree already, we'll do nothing
    }

    update_h(t);
    
    return t;   // do not forget this line!!
}



// hasn't modify!!
AvlTree make_empty(AvlTree t)
{
    if (t != NULL)
    {
        make_empty(t->left);
        make_empty(t->right);
        free(t);
    }
    return NULL;
}

Position find(ElementType x, AvlTree t)
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
Position find_min(AvlTree t)
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
Position find_min(AvlTree t)
{
    if(t == NULL)
        return NULL;

    while(t->left != NULL)
        t = t->left;    // t is a copy, a formal parameter
    return t;
}

Position find_max(AvlTree t)
{
    if(t == NULL)
        return NULL;

    while(t->right != NULL)
        t = t->right;    // t is a copy, a formal parameter
    return t;
}

AvlTree delete(ElementType x, AvlTree t)
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
