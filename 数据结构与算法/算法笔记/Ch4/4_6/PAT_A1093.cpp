#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 100005

char str[maxn];
int leftNumP[maxn] = {0};
int rightNumT[maxn] = {0};

int main()
{
    int len, ans = 0;
    scanf("%s", str);

    len = strlen(str);
    for (int i = 1; i < len; i++)   //我这里写法与书上的稍有不同，因为书上的leftNumP包括了当前位的P
    {
        if (str[i-1]=='P')
            leftNumP[i] = leftNumP[i-1]+1;
        else
            leftNumP[i] = leftNumP[i-1];
        
    }

    // int rightNumT = 0;  //这里可以优化成只使用一个int型来对右边的T计数

    for (int i = len-2; i >= 0; i--)
    {
        if (str[i+1]=='T')
            rightNumT[i] = rightNumT[i+1]+1;
            //rightNumT++;
        else
            rightNumT[i] = rightNumT[i+1];
        if (str[i]=='A')
            ans = (ans + leftNumP[i]*rightNumT[i])%1000000007;  //只是用一个数的话就可以去掉rightNumT后面的下标了
    }

    printf("%d\n", ans);

    return 0;
}