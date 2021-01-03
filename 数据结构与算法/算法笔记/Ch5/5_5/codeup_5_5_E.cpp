#include<cstdio>
#define maxn 61

int isPerfectOrAbundant(int n)
{
    int sum = 1;
    for (int i = 2; i<n; i++)
    {
        if (n%i == 0)
            sum+=i;
    }
    if (sum == n)
        return 1;
    else if (sum > n)
        return 2;
    else
        return 0;
}

int e[maxn] = {0};
int g[maxn] = {0};

int main()
{
    int eNum = 0;
    int gNum = 0;
    int ret = 0;
    for (int i = 2; i < maxn; i++)
    {
        ret = isPerfectOrAbundant(i);
        if (ret==1)
            e[eNum++] = i;
        else if (ret==2)
            g[gNum++] = i;
    }

    printf("E:");
    for (int i = 0; i < eNum; i++)
    {
        printf(" %d", e[i]);
    }

    printf(" G:");
    for (int i = 0; i < gNum; i++)
    {
        printf(" %d", g[i]);
    }

    return 0;
}