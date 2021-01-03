#include<cstdio>
#include<cmath>
#define maxn 1000

int ans[maxn] = {0};

int numOfConsFactor(int n)
{
    int curCnt = 0;     //记录当前连续因子的个数
    int curMaxCnt = 0;  //记录目前为止最长的连续因子个数
    int seqFirstFactor = 0; //目前最长连续因子序列的第一个因子
    int temp = n;
    int sqr = (int)sqrt(1.0*n);

    for (int i = 2; i <= sqr; i++)
    {
        temp = n;
        curCnt = 0;

        if (temp%i == 0)
        {
            ++curCnt;
            temp/=i;
            for (int j = i+1; i <= sqr; j++)
            {
                if (temp%j == 0)
                {
                    ++curCnt;
                    temp/=j;
                }else
                    break;
            }
            if (curCnt > curMaxCnt)
            {
                curMaxCnt = curCnt;
                seqFirstFactor = i;
            }
        }
    }

    for (int i = 0; i < curMaxCnt; i++)
    {
        ans[i] = seqFirstFactor+i;
    }
    
    return curMaxCnt;
}

int main()
{
    int N;

    scanf("%d", &N);
    //* 第一版没有过的原因是没有考虑到质数的情况

    int num = numOfConsFactor(N);
    if (num==0)
    {
        printf("1\n%d", N);
    }else
    {
        printf("%d\n", num);
        for (int i = 0; i < num; i++)
        {
            printf("%d", ans[i]);
            if (i<num-1)
                putchar('*');
        }
    }

    return 0;
}