#include<cstdio>
#define maxn 100005

int arr[maxn] = {0};

int gcd(int a, int b)
{
    return !b ? a : gcd(b, a%b);
}

int lcm(int arr[], int left, int right)
{
    if (left+1==right)
        return arr[left]/gcd(arr[left], arr[right])*arr[right];
    if (left == right)
        return arr[left];

    int mid = (left+right)/2;
    int a = lcm(arr, left, mid);    //* 二分法
    int b = lcm(arr, mid+1, right);

    return a/gcd(a, b)*b;
}

int main()
{
    int n, m;

    scanf("%d", &n);
    while (n--)
    {
        int ans = 0;
        scanf("%d", &m);
        scanf("%d", arr);
        if (m==1)
        {
            printf("%d\n", arr[0]);
            continue;
        }
        
        ans = arr[0];
        int t;
        for (int i = 1; i < m; i++)
        {
            scanf("%d", &t);
            ans = ans/gcd(ans, t)*t;    //这样的方案可以节省内存；不过好像效率没有二分法高
        }
        
        printf("%d\n", ans);

        //我的二分方案
        // for (int i = 0; i < m; i++)
        // {
        //     scanf("%d", arr+i);
        // }        
        // printf("%d\n",lcm(arr, 0, m-1));
    }

    return 0;
}