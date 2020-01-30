// parenthesis matching (Equilibrium Symbol)
// Application of Stack #1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "stack_used_array.c"

char check_ch(char ch);
int oper_ch(Stack s, char ch);
int match_ch(char ch, char top_ch);
int match_pare(char pare[], int n);

int match_pare(char pare[], int n)
{
    Stack s = NULL;
    int i;
    int is_match = 1;

    s = create_stack(n);
    if(s == NULL){
        printf("ERROR!\n");
        return 0;
    }

    for(i = 0; i < n; i++){
        if(!oper_ch(s, pare[i])){
            is_match = 0;
            break;
        }
    }

    if(i == n && !is_empty(s))
        is_match = 0;

    dispose_stack(s);
    return is_match;
}

int match_ch(char ch, char top_ch)
{
    int is_match = 0;
    switch(ch){
        case ')':
            is_match = (top_ch == '(')? 1: 0;
            break;
        case ']':
            is_match = (top_ch == '[')? 1: 0;
            break;
        case '}':
            is_match = (top_ch == '{')? 1: 0;
            break;
        default:
            break;
    }
    return is_match;
}

int oper_ch(Stack s, char ch)
{
    int is_match = 1;
    char top_ch;
    switch(check_ch(ch)){
        case 'O':
            push(ch, s);
            break;
        case 'C':
            if(!is_empty(s)){
                top_ch = top_and_pop(s);
                if(!match_ch(ch, top_ch))
                    is_match = 0;
            }else{
                is_match = 0;
            }
            break;
        case 'N':
            break;
        default:
            break;
    }
    printf("%d\n", is_match);
    return is_match;
}

char check_ch(char ch)
{
    if(ch == '(' || ch == '[' || ch == '{')
        return 'O';     // open
    else if(ch == ')' || ch == ']' || ch == '}')
        return 'C';     // close
    else
        return 'N';     // illegal
}

void test_match()
{
    char input[] = "[({})[";
    int n;
    int is_match = -1;

    n = strlen(input);
    is_match = match_pare(input, n);

    printf("is_match = %d\n", is_match);
}


int main()
{
    // test_stack();
    test_match();
    return 0;
}