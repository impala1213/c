#include <stdio.h>

float recursion(int n)
{
    if (n == 0)
        return 1.0;
    float number = 1.0 + 1.0 / recursion(n - 1);
    return number;
}

int main(void)
{
    int n;
    scanf("%d", &n);
	printf("%.5f", recursion(n));
    return 0;
}
