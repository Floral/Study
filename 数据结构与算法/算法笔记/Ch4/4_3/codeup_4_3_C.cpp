#include<cstdio>
#define maxn 20

int bag[maxn] = {0};
int count = 0;

void generateSeq(int index, int sum, int n)
{
    if (sum == 40)
    {
        count++;
        return;
    }
    if (index >= n || sum > 40)
        return;
    
    generateSeq(index+1, sum+bag[index], n);    //选择当前的物品
    generateSeq(index+1, sum, n);               //不选择当前的物品
}

int main()
{
    int n;

    while (scanf("%d", &n)!=EOF)
    {
        count = 0;
        for (size_t i = 0; i < n; i++)
        {
            scanf("%d", bag+i);
        }
        generateSeq(0, 0, n);
        printf("%d\n", count);
    }
    
    return 0;
}

// https://blog.csdn.net/SaltedfishSun/article/details/78035501
//可以对比一下上面的写法,思想都是一样的