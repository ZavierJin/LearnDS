// Maximum subsequence sum problem
// 1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#ifndef MAX
#define MAX(a,b) ((a>b)?a:b)
#endif

void swap(int* a, int* b);
void bubble_select_1(int arr[], int n);
int random_num(int min, int max);
void show_arr(int arr[], int n);
int bubble_select_2(int arr[], int n, int k);
int max_sub_seq_sum_1(const int arr[], int n);
static int max_sub_sum(const int arr[], int left, int right);
int max_sub_seq_sum_2(const int arr[], int n);

int max_sub_seq_sum_2(const int arr[], int n)
{
    printf("max_sub_seq_sum_2:\n");
    return max_sub_sum(arr, 0, n-1);
}

static int max_sub_sum(const int arr[], int left, int right)
{
    int max_left_sum, max_right_sum;
    int max_left_border_sum, max_right_border_sum;
    int left_border_sum, right_border_sum;
    int center, i;

    // base case
    if(left == right){
        if(arr[left] > 0) return arr[left];
        else return 0;
    }

    center = (left + right) / 2;
    max_left_sum = max_sub_sum(arr, left, center);
    max_right_sum = max_sub_sum(arr, center+1, right);

    // left_border_sum
    max_left_border_sum = left_border_sum = 0;
    for( i = center; i >= left; i--){
        left_border_sum += arr[i];
        if(left_border_sum > max_left_border_sum)
            max_left_border_sum = left_border_sum;
    }

    // right
    max_right_border_sum = right_border_sum = 0;
    for( i = center+1; i <= right; i++){
        right_border_sum += arr[i];
        if(right_border_sum > max_right_border_sum)
            max_right_border_sum = right_border_sum;
    }

    return MAX(MAX(max_left_sum, max_right_sum), max_left_border_sum + max_right_border_sum);
}

int max_sub_seq_sum_1(const int arr[], int n)
{
    int this_sum, max_sum, i, j;
    max_sum = 0;
    for( i = 0; i < n; i++ ){
        this_sum = 0;
        for( j = i; j < n; j++ ){
            this_sum += arr[j];

            if( this_sum > max_sum ) max_sum = this_sum;
        }
    }
    return max_sum;
}

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
    if(i%10!=0) printf("\n\n");
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

void test1()
{
    int arr[8] = {4, -3, 5, -2, -1, 2, 6, -2};
    int n = 8;
    int max_sum = 0;

    show_arr(arr, n);
    max_sum = max_sub_seq_sum_2(arr, n);
    printf("max_sum = %d\n", max_sum);
}

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
    // if(test2()!=0) return -1;
    test1();

    return 0;
}