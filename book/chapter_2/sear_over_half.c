// search a value that occurs more than half
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>


int bin_search(const int arr[], int n);

int bin_search(const int arr[], int n)
{
    int* b = NULL;
    int bk = 0;
    int key, last_ele;
    bool is_odd = false;
    int i;

    if(n < 1) return -1;   
    if(n == 1) return arr[0];

    b = (int*)malloc(sizeof(int)*(n+1)/2);
    key = last_ele = -1;
    if (n % 2 != 0)
    {
        last_ele = arr[n-1];
        is_odd = true;
        n--;
    }
    for(i = 0; i < n; i+=2)
    {
        if (arr[i] == arr[i+1])
        {
            b[bk++] = arr[i];
        }
    }

    key = bin_search(b, bk);
    free(b);

    if(key != -1)
        return key;
    else if(is_odd)
        return last_ele;
    else 
        return -1;
}

void test1()
{
    int i, n, key, ti;
    int arr[] = {3, 3, 4, 3, 4, 4, 2, 4, 3};

    n = 9;
    key = -1;

    key = bin_search(arr, n);
    if(key != -1){
        printf("key = %d\n", key);

        ti = 0;
        for(i = 0; i < n; i++){
            if(arr[i] == key) ti++;
        }

        if(ti > n/2) printf("YES\n");
        else printf("NO\n");
    }else
        printf("NOT FOUND\n");

    
}

int main()
{
    srand(time(0));
    test1();

    return 0;
}