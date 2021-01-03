#include<cstdio>
#include<cmath>
// #define maxn 1001

// int num[maxn] = {0};

int numOfFactor(int n)
{
    int cnt = 0;
    int sqr = (int)sqrt(1.0*n);

    for (int i = 1; i <= sqr; i++)
    {
        if (n%i==0)
            cnt+=2;
    }
    if (sqr == 1.0*n/sqr)
        --cnt;
    
    return cnt;
}

int main()
{
    int N, temp;

    while (scanf("%d", &N)!=EOF && N!=0)
    {
        while (N--)
        {
            scanf("%d", &temp);
            printf("%d\n", numOfFactor(temp));
        }
    }
    
    return 0;
}