// exponentiation
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

long int my_pow(long int x, unsigned int n)
{
    if(n == 0) return 1;
    if(n == 1) return x;

    if(n % 2 == 0) return my_pow(x*x, n/2);
    else return my_pow(x*x, n/2)*x;
}


int main()
{
    long int res, x;
    unsigned int n;
    scanf("%ld%u", &x, &n);
    res = my_pow(x, n);
    printf("res = %ld\n", res);

    return 0;
}