// transform infix to postfix
// Application of Stack #3
// assume that numbers are from 0 to 9
// assume that expressions are legal
// modify stack_used_array.h to change ElementType
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "stack_used_array.c"

void trans_in_to_post(char input[], char output[], int n);
char check_ch(char ch);
int oper_level(char ch);

int oper_level(char ch)
{
    int level = 0;
    switch(ch){
        case '+': case '-': 
            level = 1;
            break;
        case '*': case '/': 
            level = 2;
            break;
        case '(':
            level = 3;
            break;
        case ')':
            level = 4;
            break;
        default:
            break;
    }

    return level;
}

char check_ch(char ch)
{
    if(isdigit(ch)){
        return 'N';     // number
    }else if(isalpha(ch)){
        return 'A';
    }else if(ch == '+' || ch == '-' || ch == '*' || ch == '/' 
        || ch == '(' || ch == ')'){
        return 'O';     // operation
    }else 
        return 'I';     // illegal
}

void trans_in_to_post(char input[], char output[], int n)
{
    int i, out_index, ch_lev, top_lev;
    Stack s = NULL;
    char ch, tmp;

    s = create_stack(n);
    if(s == NULL){
        printf("ERROR!\n");
        return;
    }

    out_index = 0;
    for(i = 0; i < n && out_index < n; i++){
        ch = input[i];
        switch(check_ch(ch)){
            case 'N': case 'A':
                output[out_index++] = ch;
                break;
            case 'O':
                ch_lev = oper_level(ch);
                if(ch_lev == 4){
                    while(!is_empty(s) && (tmp = top_and_pop(s))!='(')
                        output[out_index++] = tmp;
                }else if(ch_lev != 0){
                    if(!is_empty(s))
                        top_lev = oper_level(top(s));
                    else
                        top_lev = 0;
                    
                    if(ch_lev > top_lev){
                        // printf("push %c\n", ch);
                        push(ch, s);
                    }else if(top_lev != 0){
                        while(top_lev != 3 && top_lev >= ch_lev){
                            // printf("top = %c, ch = %c\n", top(s), ch);
                            output[out_index++] = top_and_pop(s);
                            if(!is_empty(s))
                                top_lev = oper_level(top(s));
                            else 
                                break;
                        }
                        push(ch, s);
                    }
                }
                break;
            default:
                break;
        }
    }

    while(!is_empty(s) && out_index < n)
        output[out_index++] = top_and_pop(s);

    dispose_stack(s);
    if(out_index < n)
        output[out_index] = '\0';
}


void test_trans()
{
    char input[] = "a+b*c+(d*e+f)*g";
    // char input[] = "1+E*2/w";
    char* output = NULL;
    int n;

    n = strlen(input);
    output = (char*)malloc(sizeof(char)*n + 1);
    if(output == NULL){
        printf("room full\n");
        return;
    }

    printf("input:  %s\n", input);
    trans_in_to_post(input, output, n);
    printf("output: %s\n", output);
}



int main()
{
    // test_stack();
    test_trans();
    return 0;
}