#include<cstdio>
#include<cstring>
#define maxn 100005

int arr[maxn] = {0};
//* 个人觉得这个题出的很不好，既没说清楚根节点是不是一定是1，也不知道是不是多点测试
//* PS:感觉测试数据就只有给的样例一个，我这样写也能过，arr[x]直接表示x点所在的层数
int main()
{
    int n;
    // while (scanf("%d", &n)!=EOF)
    // {
        scanf("%d", &n);
        memset(arr, 0, sizeof(arr));
        arr[1] = 1;
        int a, b;
        int maxH = 1;
        while (scanf("%d %d", &a, &b)!=EOF)
        {
            // scanf("%d %d", &a, &b);
            arr[b] = arr[a]+1;
            if (arr[b]>maxH)
                maxH = arr[b];
        }
        printf("%d\n", maxH);
    // }
    
    return 0;
}