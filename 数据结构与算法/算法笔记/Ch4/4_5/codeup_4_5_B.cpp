#include<cstdio>
#include<algorithm>
#define maxn 85

//这题有毒，我认为按他的题意就是已经给定了有n组样例，所以直接while(n--)，但是这样会报错，实际你要写成while(scanf("%d")!=EOF)，然后在其中for循环
int main()
{
    int n;

    int arr[maxn] = {0};

    // while(n--)
    while (scanf("%d", &n)!=EOF)
    {
        for (int j = 0; j < n; j++)
        {
            int k;
            scanf("%d", &k);
            for (int i = 0; i < k; i++)
            {
                scanf("%d", arr+i);
            }

            int flag = 1;   //是否是第一次输出
            for (int i = 0; i < k; i++)
            {
                if (i == 0 && arr[0]!=arr[1] || i == k-1 && arr[k-1]!=arr[k-2] || (arr[i-1] > arr[i] && arr[i+1] > arr[i]) || (arr[i-1] < arr[i] && arr[i+1] < arr[i]))
                {
                    if (!flag)
                        putchar(' ');
                    flag = 0;
                    printf("%d", i);
                }
            }
            if (!flag) printf("\n");
        }
    }
    
    return 0;
}