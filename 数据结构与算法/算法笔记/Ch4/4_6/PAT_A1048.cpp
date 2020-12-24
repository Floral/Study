#include<cstdio>
#include<algorithm>
#define maxn 100005

int coins[maxn] = {0};

int main()
{
    int N, M, t, max = 0;

    scanf("%d%d", &N, &M);

    for (int i = 0; i < N; i++)
    {
        scanf("%d", coins+i);
    }

    std::sort(coins, coins+N);

    int ans;
    int i, j;
    // for (i = 0, j = N-1; i < j; i++, j--)
    // {
    //     while (i<j && coins[i]+coins[j] > M)
    //         j--;
    //     while (i<j && coins[i]+coins[j] < M)
    //         i++;
    //     if (coins[i]+coins[j] == M && coins[i]!=coins[j])
    //     {
    //         printf("%d %d\n", coins[i], coins[j]);
    //         return 0;
    //     }
    // }
    //上面是错误的写法
    for (i = 0, j = N-1; i < j;)
    {
        if (coins[i]+coins[j] == M)
            break;
        
        if (coins[i]+coins[j]<M)
            i++;
        else
            j--;
    }
    if (i<j)
    {
        printf("%d %d", coins[i], coins[j]);
    }else
    {
        printf("No Solution\n");
    }
    
    return 0;
}