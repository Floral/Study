#include<cstdio>
#include<algorithm>
#define maxn 100005

int chain[maxn] = {0};
int copyChain[maxn] = {0};  //普通版本可删

int findGE(int left, int right, int x)
{
    int mid;
    while (left < right)
    {
        mid = (left+right)/2;
        if (chain[mid] >= x)
            right = mid;
        else
            left = mid + 1;
    }
    
    return left;
}

int main()
{
    int N, M;
    int sum = 0, t;

    scanf("%d %d", &N, &M);

    for (int i = 0; i < N; i++)
    {
        scanf("%d", &t);
        sum+=t;
        chain[i+1] = sum; //chain存的是累加和
    }
#ifdef DEBUG
    for (int i = 0; i <= N; i++)
    {
        printf("%d ", chain[i]);
    }
    putchar('\n');
#endif

    int j, flag = 0;    //flag为0表示，无无损失的解，为1表示有无损失的解
    int minLoss = (1<<31)-1;

    for (int i = 0; i < N; i++)
    {
        j = findGE(i, N+1, chain[i]+M);
        if (j != N+1)
        {
            if (chain[j]-chain[i]-M <= minLoss) //普通版本小于等于也可以写成小于
            {
                minLoss = chain[j]-chain[i]-M;
                copyChain[i] = j;   //普通版本可以把这个copyChain删掉
            }
        }
    }

    //以下是普通版本
    // for (int i = 0; i < N; i++)
    // {
    //     j = findGE(i, N+1, chain[i]+M);
    //     if (j != N+1)
    //     {
    //         if (chain[j]-chain[i]-M == minLoss)
    //             printf("%d-%d\n", i+1, j);
    //     }
    // }
    
    //以下是用空间换时间的版本，相比上面的要快一些
    for (int i = 0; i < N; i++)
    {
        if (copyChain[i]!=0 && chain[copyChain[i]]-chain[i]-M == minLoss)
            printf("%d-%d\n", i+1, copyChain[i]);
    }
    return 0;
}