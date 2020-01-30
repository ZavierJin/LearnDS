/* 测试两种不同算法的时间 */
#include <stdio.h>
#include <math.h>
#include <time.h>

#define MAXN 10   //最高次方
#define MAXK 1e7  //测试次数


double f1( int n, double a[], double x)
{
    int i;
    double p = a[0];
    for( i=1; i<=n; ++i )
        p += (a[i] * pow(x, i));
    return p;
}

double f2( int n, double a[], double x )
{
    int i;
    double p = a[n];
    for ( i=n; i>0; --i )
        p = a[i-1] + x*p;
    return p;
}

void test(int id)
{
    clock_t  start, stop;
    /* clock_t是clock()函数返回的变量类型 */
    double duration;
    /* 记录被测函数的运行时间，以秒为单位 */
    int i;
    double a[MAXN];
    for ( i=0; i<MAXN; ++i ) 
        a[i] = (double)i;


    start = clock();
    // my function
    for ( i=0; i<MAXK; ++i ){
        switch(id){
            case 1: f1(MAXN-1, a, 1.1); break;
            case 2: f2(MAXN-1, a, 1.1); break;
            default:
                printf("Wrong id!");
                break;
        }
    }
    stop = clock();
    duration = ((double)(stop - start))/CLK_TCK;
    printf("ticks1 = %f\n", (double)(stop - start));
    printf("duration1 = %6.2e\n", duration);

}

int main(void)
{
    test(1);
    test(2);

    return 0;
}