#include<cstdio>
#include<algorithm>

int N, seq[20];
int sum = 0, count = 0;

void generateP(int n)
{
    for (size_t i = 1; i <= 2; i++)
    {
        if (sum+i < N)
        {
            seq[n] = i;
            sum+=i;
            generateP(n+1);
            sum-=i;
        }else if (sum+i == N)
        {
            seq[n] = i;
            count++;
        }else
        {
            break;
        }
    }
}

// int getNum(int N)  //N是剩余巧克力数
// {
//     if (N == 1)     //如果只剩一块，只有一种方案
//         return 1;
//     if (N == 2)     //如果还剩两块，有两种方案
//         return 2;
//     return getNum(N-1) + getNum(N-2);   //如果大于两块，可以看今天吃1块后有多少种方案，再加上如果今天吃两块的的方案数
// }

int main()
{

    while (scanf("%d", &N)!=EOF)
    {
        count = 0;
        generateP(0);
        printf("%d\n", count);
    }
    
    return 0;
}