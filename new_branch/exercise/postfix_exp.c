/* 后缀表达式运算 */
#include<stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef double ElementType;
#define Infinity 1e8
#define Max_Expr 30   /* max size of expression */

ElementType EvalPostfix( char *expr );

int main()
{
    ElementType v;
    char expr[]="11 -2 5.5 * + 23 7 / -";
    // char expr[]="11 2 +";
    v = EvalPostfix( expr );
    if ( v < Infinity )
        printf("%f\n", v);
    else
        printf("ERROR\n");
    return 0;
}

/* Your function will be put here */
#include <stdbool.h>
typedef int Position;
#ifndef ERROR
#define ERROR 1e7
#endif
struct SNode {
    ElementType *Data; /* 存储元素的数组 */
    Position Top;      /* 栈顶指针 */
    int MaxSize;       /* 堆栈最大容量 */
};
typedef struct SNode *Stack;
 
Stack CreateStack( int MaxSize )
{
    Stack S = (Stack)malloc(sizeof(struct SNode));
    S->Data = (ElementType *)malloc(MaxSize * sizeof(ElementType));
    S->Top = -1;
    S->MaxSize = MaxSize;
    return S;
}
 
bool IsFull( Stack S )
{
    return (S->Top == S->MaxSize-1);
}
 
bool Push( Stack S, ElementType X )
{
    if ( IsFull(S) ) {
        return false;
    }
    else {
        S->Data[++(S->Top)] = X;
        return true;
    }
}
 
bool IsEmpty( Stack S )
{
    return (S->Top == -1);
}
 
ElementType Pop( Stack S )
{
    if ( IsEmpty(S) ) {
        return ERROR; /* ERROR是ElementType的特殊值，标志错误 */
    }
    else 
        return ( S->Data[(S->Top)--] );
}



ElementType EvalPostfix( char *expr )
{
    Stack S = NULL;
    int i, j, beg, end;
    char num[100];
    char ch;
    double num_1, num_2;
    i = j = beg = end = 0;

    S = CreateStack(Max_Expr);
    
    while(expr[i]!='\0'){
        ch=expr[i];
        if(ch=='+' || ch=='*' || ch=='/' || (ch=='-'&&!isalnum(expr[i+1]))){
            switch(ch){
                case '+':
                    num_2 = Pop(S);
                    num_1 = Pop(S);
                    if(num_1==ERROR || num_2==ERROR) return Infinity;
                    else Push(S, num_1 + num_2);
                    break;
                case '-':
                    num_2 = Pop(S);
                    num_1 = Pop(S);
                    if(num_1==ERROR || num_2==ERROR) return Infinity;
                    else Push(S, num_1 - num_2);
                    break;
                case '*':
                    num_2 = Pop(S);
                    num_1 = Pop(S);
                    if(num_1==ERROR || num_2==ERROR) return Infinity;
                    else Push(S, num_1 * num_2);
                    break;
                case '/':
                    num_2 = Pop(S);
                    num_1 = Pop(S);
                    if(num_1==ERROR || num_2==ERROR || num_2==0) return Infinity;
                    else Push(S, num_1 / num_2);
                    break;
                default: 
                    return Infinity;
            }
        }else if(isalnum(ch) || ch=='.' || ch=='-'){
            for(beg=i, end=i; expr[end]!='\0' && expr[end]!=' '; ++end)
                continue;
            end--;
            for(j=beg; j<=end; ++j)
                num[j-beg] = expr[j];
            num[j-beg] = '\0';
            if(IsFull(S)) return Infinity;
            else Push(S, atof(num));
            i = end;
        }
        i++;
    }

    num_1 = Pop(S);
    if(num_1==ERROR || !IsEmpty(S)) return Infinity;
    else return num_1;
}
