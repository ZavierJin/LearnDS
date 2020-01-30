// check if a list has value with index equals the value
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>


void swap(int* a, int* b);
void bubble_select_1(int arr[], int n);
int random_num(int min, int max);
void show_arr(const int arr[], int n);
int check(const int arr[], int n);
int search(const int arr[], int n);
int search_1(const int arr[], int left, int right);


int search(const int arr[], int n)
{
    return search_1(arr, 0, n-1);
}

int search_1(const int arr[], int left, int right)
{
    int mid, index;
    mid = (left + right) / 2;
    index = -1;

    if(arr[mid] == mid) return mid;
    else if(mid == right) return -1;

    if(arr[mid] < mid) index = search_1(arr, mid+1, right);
    else index = search_1(arr, left, mid);

    return index;
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
            if(arr[j]>arr[j+1]) swap(arr+j, arr+j+1);
        }
    }
    
}

int check(const int arr[], int n)
{
    int i;
    bool is_find = false;

    for(i = 0; i < n; i++){
        if(arr[i] == i){
            is_find = true;
            break;
        }
    }
    if(is_find) return i;
    else return -1;
}

void show_arr(const int arr[], int n)
{
    int i;
    for(i=0; i<n; i++){
        printf("%3d%c", arr[i], (i%10==9)?'\n':' ');
    }
    if(i%10!=0) printf("\n\n");
}

int random_num(int min, int max)
{
    int inter;
    inter = max - min + 1;
    return rand()%inter+min;
}

int test2()
{
    int i, n;
    int* arr = NULL;
    int index = -1;
    n = 40;

    // create a strictly increasing list
    if((arr=(int*)malloc(sizeof(int)*3*n))==NULL){
        return -1;
    }
    for(i=0; i<3*n; i++){
        arr[i] = i-n;
    }
    for(i=0; i<3*n; i++){
        swap(arr+i, arr+random_num(0, i));
    }
    show_arr(arr, n);
    printf("\n");

    bubble_select_1(arr, n);
    show_arr(arr, n);
    printf("\n");

    index = check(arr, n);
    if(index != -1) printf("Find, index = %d\n", index);
    else printf("NOT FIND\n");

    index = search(arr, n);
    if(index != -1) printf("Find, index = %d\n", index);
    else printf("NOT FIND\n");

    return 0;
}


int main()
{
    srand(time(0));
    test2();

    return 0;
}