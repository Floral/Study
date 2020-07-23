#include<cstdio>

const int maxn = 210;

int main()
{
    int n, x, i;
    int arr[maxn] = {0};

    while(scanf("%d", &n)!=EOF)
    {
        for (i = 0; i < n; ++i)
        {
            scanf("%d", arr+i);
        }
        scanf("%d", &x);
        for (i = 0; i < n; ++i)
        {
            if (arr[i] == x)
            {
                printf("%d\n", i);
                break;
            }
        }
        if (i == n)
            printf("-1\n");
    }

    return 0;
}