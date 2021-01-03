#include<cstdio>
#define maxn 1000001

int prime[maxn] = {0};
bool p[maxn] = {false};
int pNum = 0;

void Find_Prime()
{
    for (int i = 2; i < maxn; i++)
    {
        if (p[i] == false)
        {
            prime[pNum++] = i;
            for (int j = i+i; j < maxn; j+=i)
            {
                p[j] = true;
            }
        }
    }
}

int main()
{
    Find_Prime();

    int k;
    while (scanf("%d", &k)!=EOF)
    {
        printf("%d\n", prime[k-1]);
    }
    
    return 0;
}