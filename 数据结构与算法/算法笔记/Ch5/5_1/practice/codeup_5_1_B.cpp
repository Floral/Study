#include<cstdio>

int reverse(int N)
{
    int ans = 0;

    for (int i = 0; i < 4; i++)
    {
        ans = ans*10 + N%10;
        N/=10;
    }
    
    return ans;
}

int main()
{
    for (int N = 1000; N <= 1111; N++)
    {
        if (N*9==reverse(N))
            printf("%d\n", N);
    }
    
    return 0;
}