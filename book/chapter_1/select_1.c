// selection problem
// 1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void swap(int* a, int* b);
void bubble_select_1(int arr[], int n);
int random_num(int min, int max);
void show_arr(int arr[], int n);
int bubble_select_2(int arr[], int n, int k);

int bubble_select_2(int arr[], int n, int k)
{
    int* buf;
    int i, j, m;
    buf = (int*)malloc(sizeof(int)*k);

    for(i=0; i<k; i++){
        buf[i] = arr[i];
    }
    bubble_select_1(buf, k);
    show_arr(buf, k);
    for(i=k; i<n; i++){
        for(j=0; j<k; j++){
            if(arr[i]>buf[j]){
                for(m=k-1; m>j; m--) buf[m]=buf[m-1];
                buf[j]=arr[i];
                show_arr(buf, k);
                break;
            }
        }
    }

    return buf[k-1];
}

void show_arr(int arr[], int n)
{
    int i;
    for(i=0; i<n; i++){
        printf("%3d%c", arr[i], (i%10==9)?'\n':' ');
    }
    if(i%4!=0) printf("\n");
}

int random_num(int min, int max)
{
    int inter;
    inter = max - min;
    return rand()%inter+min;
}

void swap(int* a, int* b)
{
    int tem;
    tem = *b;
    *b = *a;
    *a = tem;
}

void bubble_select_1(int arr[], int n)
{
    int i, j;

    for(i=0; i<n-1; i++){
        for(j=0; j<n-i-1; j++){
            if(arr[j]<arr[j+1]) swap(arr+j, arr+j+1);
        }
    }
    
}

// void test1()
// {
//     int key, i;
//     int n=9;
//     int k=4;
//     int arr[9] = {2, 13, 4, 9, 1, 24, 23, 8, 1};
//     key = bubble_select_1(arr, n, k);
//     for(i=0; i<n; i++){
//         printf("%3d%c", arr[i], (i%10==9)?'\n':' ');
//     }
    
//     printf("k = %d, key = %d\n", k, key);
// }

int test2()
{
    int key = -1;
    int i, n, k;
    int* arr = NULL;
    n = 50;
    k = 10;
    if((arr=(int*)malloc(sizeof(int)*n))==NULL){
        return -1;
    }
    for(i=0; i<n; i++){
        arr[i] = random_num(0, 99);
    }
    show_arr(arr, n);
    key = bubble_select_2(arr, n, k);
    bubble_select_1(arr, n);
    show_arr(arr, n);
    printf("k = %d, key = %d\n", k, key);

    return 0;
}

int main()
{
    srand(time(0));
    if(test2()!=0) return -1;

    return 0;
}