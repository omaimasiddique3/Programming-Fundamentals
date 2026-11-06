#include <stdio.h>

// Programmer: Omaima Siddique
// Roll no.: 26K-2517
// Class: BDS-1A
// Desc: Amicable Pairs

int sumProperDivisors(int x)
{
    int i, sum;
    if (x <= 1) return 0;
    sum = 1;
    for (i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            sum += i;
            if (i != x / i) sum += x / i;
        }
    }
    return sum;
}

int main(void)
{
    int n, a, b, count = 0;

    printf("Enter n: ");
    scanf("%d", &n);

    printf("Amicable pairs up to %d:\n", n);
    for (a = 2; a <= n; a++) {
        b = sumProperDivisors(a);
        if (b > a && b <= n && sumProperDivisors(b) == a) {
            printf("(%d, %d)\n", a, b);
            count++;
        }
    }
    if (count == 0)
        printf("No amicable pairs found up to %d.\n", n);
    else
        printf("Total pairs: %d\n", count);
    return 0;
}
