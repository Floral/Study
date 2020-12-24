#include<cstdio>
#include<algorithm>
#define maxn 1005

int P[maxn] = {0};

int main()
{
    int C, n, V, W;
    
    scanf("%d", &C);
    while (C--)
    {
        scanf("%d%d%d", &n, &V, &W);
        for (int i = 0; i < n; i++)
        {
            scanf("%d", P+i);
        }
        std::sort(P, P+n);  //按浓度从低到高排

        int count = 0;  //最多可以用几瓶药水        
        double t = .0;  //临时变量
        for (int i = 0; i < n; i++)
        {
            if ((t+P[i])/(double)(count+1) <= W) //如果加上当前这瓶药水之后,浓度满足要求,则继续
            {
                t += P[i];
                count++;
            }else   //不满足则退出
                break;
        }
        if (count == 0)
            printf("0 0.00\n");
        else
            printf("%d %.2f\n", V*count, (int)(t/count+0.5)/100.0); //保留两位小数的写法，虽然直接t/count/100也能过oj...
    }
    return 0;
}