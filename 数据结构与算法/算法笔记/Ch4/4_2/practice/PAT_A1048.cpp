#include<cstdio>
#define maxn 510
//散列版本的解法

int coins[maxn] = {0};

int main()
{
    int N, M, t, max = 0;

    scanf("%d%d", &N, &M);

    for (int i = 0; i < N; i++)
    {
        scanf("%d", &t);
        coins[t]++;
        if (t > max)
            max = t;
    }
    
    for (int i = 1; i <= max; i++)
    {
        if (coins[i]!=0)
        {
            coins[i]--; //消耗第一枚硬币
            if (coins[M-i]!=0)
            {
                printf("%d %d\n", i, M-i);
                return 0;
            }
            coins[i]++; //如果不存在解则加回来
        }
    }
    printf("No Solution\n");

    return 0;
}