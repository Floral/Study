#include<cstdio>
#include<cstring>
#define maxn 11

int factor[maxn] = {0};

int main()
{
    int m, n, x;

    scanf("%d", &m);
    while (m--)
    {
        int ans = 0;
        memset(factor, 0, sizeof(factor));
        scanf("%d", &n);

        for (int i = 0; i < n+1; i++)
        {
            scanf("%d", factor+i);
        }
        scanf("%d", &x);

        for (int i = n; i >= 0; i--)
        {
            ans = ans*x + factor[i];
        }
        printf("%d\n", ans);
    }
    
    return 0;
}