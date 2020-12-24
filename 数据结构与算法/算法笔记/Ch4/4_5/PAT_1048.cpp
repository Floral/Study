#include<cstdio>
#include<algorithm>
#define maxn 100005

int coins[maxn] = {0};
int findGE(int left, int right, int x)
{
    int mid;
    while (left<right)
    {
        mid = (left+right)/2;
        if (coins[mid] == x)
            return mid;
        if (coins[mid] >= x)
            right = mid;
        else
            left = mid+1;
    }
    
    return left;
}

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
    for (int i = 0; i < N; i++)
    {
        ans = findGE(i, N, M-coins[i]); //这里的范围应该还是从i开始，而不是0，因为最终会输出的答案要求是V1<=V2
        if (ans!=N)
        {
            if (ans != i && coins[ans] == M-coins[i])
            {
                printf("%d %d\n", coins[i], coins[ans]);
                return 0;
            }else if (ans == i && coins[ans+1] == coins[ans])
            {
                printf("%d %d\n", coins[i], coins[ans]);
                return 0;
            }
        }
    }

    printf("No Solution\n");

    return 0;
}