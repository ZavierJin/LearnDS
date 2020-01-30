// Maximum subsequence sum problem
// If all integers are negative, max_sum is 0
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#ifndef MAX
#define MAX(a,b) ((a>b)?a:b)
#endif


int random_num(int min, int max);
void show_arr(const int arr[], int n);
int max_sub_seq_sum_1(const int arr[], int n);
static int max_sub_sum(const int arr[], int left, int right);
int max_sub_seq_sum_2(const int arr[], int n);
int max_sub_seq_sum_3(const int arr[], int n);

// O(N) ????
int max_sub_seq_sum_3(const int arr[], int n)
{
    int this_sum, max_sum, j;

    this_sum = max_sum = 0;
    for(j = 0; j < n; j++){
        this_sum += arr[j];

        if(this_sum > max_sum)
            max_sum = this_sum;
        else if(this_sum < 0)
            this_sum = 0;
    }

    printf("max_sub_seq_sum_3:\n");
    return max_sum;
}

// O(NlogN)
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

// O(N*N)
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
    inter = max - min;
    return rand()%inter+min;
}

void test1()
{
    int arr[8] = {4, -3, 5, -2, -1, 2, 6, -2};
    int n = 8;
    int max_sum = 0;

    show_arr(arr, n);
    max_sum = max_sub_seq_sum_3(arr, n);
    printf("max_sum = %d\n", max_sum);
    printf("right answer = 11\n");
}


int main()
{
    srand(time(0));
    test1();

    return 0;
}