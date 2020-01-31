/* 7-8 File Transfer */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 10000
#define MAX_CHECK 10000

int Computers[MAX_NODES+1];
int Output[MAX_CHECK];
int output_id = 0;

void insert( int X, int Y );
void check( int X, int Y );
void check_all();
void show_output();
void init_union();

int main(void)
{
    int N;
    int x, y;
    char op;

    scanf("%d\n", &N);
    Computers[0] = N;

    init_union();
    while( scanf("%c", &op)==1 && op!='S'){
        scanf("%d %d\n", &x, &y);
        switch(op){
            case 'C': check(x, y); break;
            case 'I': insert(x, y); break;
        }
    }
    show_output();
    return 0;
}

void init_union()
{
    int i;
    for(i=1; i<MAX_NODES+1; ++i)
        Computers[i] = -1;
}

void show_output()
{
    int i;
    for(i=0; i<output_id; ++i){
        if(Output[i]) printf("yes\n");
        else printf("no\n");
    }
    check_all();
    return;
}

void check_all()
{
    int *compo_list = NULL;
    int total_comp = 0;
    int sum = 0;
    int i, j;

    compo_list = (int *)malloc(sizeof(int)*(Computers[0]+1));
    for(i=1; i<=Computers[0]; ++i)
        compo_list[i] = 0;

    i = j = 1;
    while(i<=Computers[0] && sum<=Computers[0]){
        j = i;
        while( Computers[j]>0 ) j = Computers[j];
        if(!compo_list[j]){
            compo_list[j] = 1;
            total_comp++;
            sum += (-Computers[j]);
        }
        i++;
    }
    if( total_comp == 1 )
        printf("The network is connected.\n");
    else
        printf("There are %d components.\n", total_comp);
}

void check( int X, int Y )
{
    bool is_connect = false;
    if( X <= Computers[0] && Y <= Computers[0] ){
        while( Computers[X]>0 ) X = Computers[X];
        while( Computers[Y]>0 ) Y = Computers[Y];
        is_connect = (X!=Y)?false:true;
    }

    Output[output_id++] = (is_connect)?1:0; 
    
    return ;
}

void insert( int X, int Y )
{
    if( X > Computers[0] || Y > Computers[0] )
        return;

    while( Computers[X]>0 ) X = Computers[X];
    while( Computers[Y]>0 ) Y = Computers[Y];

    if( Computers[X] > Computers[Y] ){
        Computers[Y] += Computers[X];
        Computers[X] = Y;
    }else{
        Computers[X] += Computers[Y];
        Computers[Y] = X;
    }
    return;
}