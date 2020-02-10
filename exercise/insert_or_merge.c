/* 7-13 Insert or Merge */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MAX_NUM 100
typedef int ElementType;

int Input[MAX_NUM];
int Target[MAX_NUM];

void test( ElementType A[], int N );
void copy( ElementType A[], int N );
void Merge_Sort( ElementType A[], int N );
bool InsertionSort( ElementType A[], int N );

int main(void)
{
    int N, i;
    int A[MAX_NUM];

    scanf("%d",&N);
    for(i=0; i<N; ++i)
        scanf("%d",&Input[i]);
    for(i=0; i<N; ++i)
        scanf("%d",&Target[i]);

    copy(A, N);
    if(InsertionSort(A, N)){
        printf("Insertion Sort\n");
        test(A, N);
    }else{
        copy(A, N);
        Merge_Sort(A, N);
        printf("Merge Sort\n");
        test(A, N);
    }
    return 0;
}

void test( ElementType A[], int N )
{
    int i;
    for(i=0; i<N-1; ++i){
        printf("%d ", A[i]);
    }
    printf("%d\n", A[i]);
    return ;
}

void copy( ElementType A[], int N )
{
    int i;
    for(i=0; i<N; ++i){
        A[i] = Input[i];
    }
    return ;
}

bool check( ElementType A[], int N )
{
    int i;
    for(i=0; i<N; ++i){
        if(A[i]!=Target[i])
            return false;
    }
    return true;
}


/* 归并排序 - 循环实现 */
/* L = 左边起始位置, R = 右边起始位置, RightEnd = 右边终点位置*/
void Merge( ElementType A[], ElementType TmpA[], int L, int R, int RightEnd )
{ /* 将有序的A[L]~A[R-1]和A[R]~A[RightEnd]归并成一个有序序列 */
     int LeftEnd, NumElements, Tmp;
     int i;
      
     LeftEnd = R - 1; /* 左边终点位置 */
     Tmp = L;         /* 有序序列的起始位置 */
     NumElements = RightEnd - L + 1;
      
     while( L <= LeftEnd && R <= RightEnd ) {
         if ( A[L] <= A[R] )
             TmpA[Tmp++] = A[L++]; /* 将左边元素复制到TmpA */
         else
             TmpA[Tmp++] = A[R++]; /* 将右边元素复制到TmpA */
     }
 
     while( L <= LeftEnd )
         TmpA[Tmp++] = A[L++]; /* 直接复制左边剩下的 */
     while( R <= RightEnd )
         TmpA[Tmp++] = A[R++]; /* 直接复制右边剩下的 */
          
     for( i = 0; i < NumElements; i++, RightEnd -- )
         A[RightEnd] = TmpA[RightEnd]; /* 将有序的TmpA[]复制回A[] */
}
 
/* length = 当前有序子列的长度*/
void Merge_pass( ElementType A[], ElementType TmpA[], int N, int length )
{ /* 两两归并相邻有序子列 */
     int i, j;
       
     for ( i=0; i <= N-2*length; i += 2*length )
         Merge( A, TmpA, i, i+length, i+2*length-1 );
     if ( i+length < N ) /* 归并最后2个子列*/
         Merge( A, TmpA, i, i+length, N-1);
     else /* 最后只剩1个子列*/
         for ( j = i; j < N; j++ ) TmpA[j] = A[j];
}
 
void Merge_Sort( ElementType A[], int N )
{ 
     int length; 
     ElementType *TmpA;
     int unfinish = 1;
      
     length = 1; /* 初始化子序列长度*/
     TmpA = malloc( N * sizeof( ElementType ) );
     if ( TmpA != NULL ) {
          while( length < N) {
              Merge_pass( A, TmpA, N, length );
              unfinish++;
              if(unfinish==0) break;
              if(check(TmpA, N)) unfinish = -1;
              length *= 2;
              Merge_pass( TmpA, A, N, length );
              unfinish++;
              if(unfinish==0) break;
              if(check(TmpA, N)) unfinish = -1;
              length *= 2;
          }
          free( TmpA );
     }
     else printf( "空间不足" );
}
/* 插入排序 */
bool InsertionSort( ElementType A[], int N )
{ 
    int P, i;
    ElementType Tmp;
    bool is_same = false;

    for ( P=1; P<N; P++ ) {
        Tmp = A[P]; /* 取出未排序序列中的第一个元素*/
        for ( i=P; i>0 && A[i-1]>Tmp; i-- )
            A[i] = A[i-1]; /*依次与已排序序列中元素比较并右移*/
        A[i] = Tmp; /* 放进合适的位置 */
        // test(A, N);
        if(check(A, N) && P<N-1){
            is_same = true;
            P++;
            Tmp = A[P]; /* 取出未排序序列中的第一个元素*/
            for ( i=P; i>0 && A[i-1]>Tmp; i-- )
                A[i] = A[i-1]; /*依次与已排序序列中元素比较并右移*/
            A[i] = Tmp; /* 放进合适的位置 */
            break;
        }
    }

    return is_same;
}