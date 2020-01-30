// Postfix Expression
// Application of Stack #2
// assume that numbers are from 0 to 9
// modify stack_used_array.h to change ElementType
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "stack_used_array.c"

int postfix_exp(char exp[], int n);
char check_ch(char ch);
// int operation(int num_1, int num_2);


char check_ch(char ch)
{
    if(ch >= '0' && ch <= '9'){
        return 'N';     // number
    }else if(ch == '+' || ch == '-' || ch == '*' || ch == '/'){
        return 'O';     // operation
    }else 
        return 'I';     // illegal
}

int postfix_exp(char exp[], int n)
{
    Stack s = NULL;
    int i, num_1, num_2, res;
    char ch;
    int is_error = 0;

    s = create_stack(n);
    if(s == NULL){
        printf("ERROR!\n");
        return 0;
    }

    for(i = 0; i < n && !is_error; i++){
        ch = exp[i];
        switch(check_ch(ch)){
            case 'N':
                push(ch-'0', s);
                break;
            case 'O':
                num_1 = top_and_pop(s);
                num_2 = top_and_pop(s);
                // need to create a new function 
                switch(ch){
                    case '+': res = num_2 + num_1; break;
                    case '-': res = num_2 - num_1; break;
                    case '*': res = num_2 * num_1; break;
                    case '/': 
                        if(num_1 == 0){
                            printf("Error!\n");
                            is_error = 1;
                        }else 
                            res = num_2 / num_1;
                        break;
                    default:
                        break;
                }
                if(!is_error) push(res, s);
                break;
            default:
                printf("Error2\n");
                is_error = 1;
                break;
        }
    }

    if(!is_error){
        res = top_and_pop(s);
        is_error = !is_empty(s);
    }

    if(!is_error)
        return res;
    else
        return 0;
}



void test_postfix()
{
    char input[] = "6523+8*+3+*";
    int n;
    int res = 0;

    n = strlen(input);
    res = postfix_exp(input, n);

    printf("res = %d\n", res);
}



int main()
{
    // test_stack();
    test_postfix();
    return 0;
}