// Stack (use array)
// need to declare the array size at the beginning

#ifndef _STACK_H
    #define _STACK_H 

    struct StackRecord;
    typedef struct StackRecord *Stack;

    typedef char ElementType;   // modify

    int is_empty(Stack s);
    int is_full(Stack s);
    Stack create_stack(int max_elements);
    void dispose_stack(Stack s);
    void make_empty(Stack s);
    void push(ElementType x, Stack s);
    ElementType top(Stack s);
    void pop(Stack s);
    ElementType top_and_pop(Stack s);

#endif  /* _STACK_H */

