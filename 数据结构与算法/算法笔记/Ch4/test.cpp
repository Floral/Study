#include<cstdio>
#include<cmath>

unsigned int fibo(unsigned int n)
{
    if (n == 0 || n == 1)
        return 1;
    return fibo(n-1)+fibo(n-2);
}

unsigned int fibo_dp(int n)
{
    unsigned int arr[n+1] = {0};
    for (size_t i = 0; i < n+1; i++)
    {
        if (i == 0 || i == 1)
            arr[i] = 1;
        else
            arr[i] = arr[i-1]+arr[i-2];
    }
    return arr[n];
}

int main()
{
    // unsigned int a = fibo(40);
    size_t a = 1;
    int b = 5;
    int res = abs(a-b);
    printf("%d\n", res);
    return 0;
}