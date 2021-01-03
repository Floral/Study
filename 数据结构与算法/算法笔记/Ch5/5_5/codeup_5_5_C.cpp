#include<cstdio>
#define maxn 1001

int prime[maxn] = {0};
bool p[maxn] = {false};
int pNum = 0;

void findPrime()
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

int primeFactor(int n)
{
    int cnt = 0;
    for (int i = 0; i < pNum && prime[i]<n; i++)
    {
        if (n%prime[i] == 0)
        {
            while (n%prime[i]==0)
            {
                ++cnt;
                n/=prime[i];
            }
        }
    }

    if (n>1)
    {
        ++cnt;
    }
    return cnt;
}

int main()
{
    int N;
    findPrime();
    while (scanf("%d", &N)!=EOF)
    {
        printf("%d\n", primeFactor(N));
    }

    return 0;
}