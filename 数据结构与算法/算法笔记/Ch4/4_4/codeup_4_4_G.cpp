#include<cstdio>
#include<algorithm>

int arr[5] = {50, 20, 10, 5, 1};

int main()
{
    int money;

    while (scanf("%d", &money)!=EOF)
    {
        int num[5] = {0};
        for (int i = 0; i < 5 && money > 0;)
        {
            if (money - arr[i] >= 0)
            {
                money-=arr[i];
                num[i]++;
            }else
                i++;
        }
        int flag = 1;   //是否是第一个输出的
        for (int i = 0; i < 5; i++)
        {
            if (num[i]!=0)
            {
                if (flag)
                    flag = 0;
                else
                    putchar('+');
                printf("%d*%d",arr[i], num[i]);
            }
        }
        printf("\n");
    }
    
    return 0;
}