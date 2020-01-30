// Euclidean algorithm
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

unsigned int gcd(unsigned int m, unsigned int n);

unsigned int gcd(unsigned int m, unsigned int n)
{
    unsigned int rem;

    while(n > 0){
        rem = m % n;
        m = n;
        n = rem;
    }
    return m;
}

int main()
{
    unsigned int m, n;
    scanf("%u%u", &m, &n);
    m = gcd(m, n);
    printf("gcd = %u\n", m);

    return 0;
}