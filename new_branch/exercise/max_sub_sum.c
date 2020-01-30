//最大子序列和
#include<stdio.h>
#define MAX_SIZE 100000
#define MAX(a,b) ((a>b)?(a):(b))
// long find_max(int a[], int m, int n);



int main(void)
{
    // // O(nlogn)
    // long k;
    // int a[MAX_SIZE];
    // scanf("%ld",&k);
    // for(int i=0; i<k; ++i )
    //     scanf("%d", &a[i]);
    
    // printf("%d", find_max(a,0,k-1));

    // O(n)
    int a[MAX_SIZE];
    long k;
    long this_sum, max_sum;
    int n;
    int first, last, max_first, max_last;
    int all_neg = 1;

    first = last = -1;
    max_first = max_last = -1;
    this_sum = max_sum = 0;
    scanf("%ld",&k);

    for(int i=0; i<k; ++i ){
        scanf("%d",&n);
        a[i] = n;
        this_sum += n;
        last = i;
        if(this_sum < 0){
            this_sum = 0;
            first = last = -1;
        }else if(first == -1)
            first = i;

        if(this_sum > max_sum){
            max_sum = this_sum;
            max_first = first;
            max_last = last;
        }
    }
    printf("%ld", max_sum);
    if(max_sum > 0)
        printf(" %d %d\n", a[max_first], a[max_last]);
    else{
        for(int i=0; i<k; ++i){
            if(a[i]==0){
                all_neg = 0;
                break;
            }
        }
        if(all_neg)
            printf(" %d %d\n", a[0], a[k-1]);
        else
            printf(" 0 0\n");
    }
        
    return 0;
}

// long find_max(int a[], int m, int n)
// {
//     long max_sum = 0;
//     long left_max_sum, right_max_sum, this_sum;
//     long left_sum, mid_sum, right_sum;
//     left_max_sum = right_max_sum = this_sum = 0;
//     left_sum = mid_sum = right_sum = 0;

//     if(m == n) max_sum = a[m];
//     else{
//         left_sum = find_max(a, m, (m+n)/2);
//         right_sum = find_max(a, (m+n)/2+1, n);

//         left_max_sum = right_max_sum = this_sum = 0;
//         for(int i=(m+n)/2; i>=m; --i){
//             this_sum += a[i];
//             if(this_sum > left_max_sum) left_max_sum = this_sum;
//         }
//         this_sum = 0;
//         for(int i=(m+n)/2+1; i<=n; ++i){
//             this_sum += a[i];
//             if(this_sum > right_max_sum) right_max_sum = this_sum;
//         }
//         max_sum = MAX(MAX(left_sum, right_sum), left_max_sum+right_max_sum);
//     }
//     return max_sum;
// }