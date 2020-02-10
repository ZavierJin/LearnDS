/* 7-16 Sort with Swap(0, i) */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MAX_NUM 100000

// long search(int arr[], long num, long N)
// {
//     int i;
//     for(i=0; i<N; ++i)
//         if(arr[i]==num)
//             return i;
//     printf("ERROR\n");
//     return -1;
// }

int main(void)
{
    long N, i, index, sum;
    int arr[MAX_NUM];
    int visit[MAX_NUM];
    int ptr[MAX_NUM];   // 记录值为arr[i]数的存放下标，便于查找

    scanf("%ld", &N);
    for(i=0; i<N; ++i){
        scanf("%d", &arr[i]);
        ptr[arr[i]] = i;
        visit[i] = 0;
        if(arr[i]==0)
            index = i;
    }

    sum = 0;
    while(index!=0){
        visit[index] = 1;
        index = ptr[index];
        sum++;
    }

    for(i=1; i<N; ++i){
        if(visit[i]) continue;
        if(arr[i] == i) visit[i] = 1;
        else{
            index = i;
            // printf("%ld\n", index);
            while(index!=arr[i]){
                visit[index] = 1;
                index = ptr[index];
                sum++;
            }
            visit[index] = 1;
            sum+=2;
            // printf("%ld\n", sum);
        }
    }
    printf("%ld\n", sum);
    return 0;
}
