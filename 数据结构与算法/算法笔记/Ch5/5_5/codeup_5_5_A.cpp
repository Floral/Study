#include<cstdio>
#include<cmath>
#define maxn 1001

int prime[maxn] = {0};
bool p[maxn] = {false};
int pNum = 0;

bool isPrime(int n)
{
    if (n<2)
        return false;

    int sqr = (int)sqrt(1.0*n);
    for (int i = 2; i <= sqr; i++)
    {
        if (n%i == 0)
            return false;
    }
    return true;
}

void Find_Prime()
{
    for (int i = 2; i < maxn; i++)
    {
        if (!p[i])
        {
            prime[pNum++] = i;
            for (int j = i+i; j < maxn; j+=i)
                p[j] = true;
        }
    }
}

bool isPerfect(int n)
{
    int sum = 1;
    for (int i = 2; i<n; i++)
    {
        if (n%i == 0)
            sum+=i;
    }
    if (sum == n)
        return true;
    else
        return false;
}

int main()
{
    int n;

    while (scanf("%d", &n)!=EOF)
    {
        int first = true;
        for (int i = 2; i <= n; i++)
        {
            if (isPerfect(i))
            {
                if (!first)
                    putchar(' ');
                first = false;
                printf("%d", i);
            }
        }
        putchar('\n');
    }

    return 0;
}