#include<cstdio>
#include<algorithm>
#define maxn 110

int a[maxn] = {0};
// int b[maxn] = {0};

bool binSearch(int left, int right, int x)
{
    int mid;

    while (left <= right)
    {
        mid = (left+right)/2;
        if (a[mid] == x)
            return true;   //找到了
        if (a[mid] > x)
            right = mid-1;
        else
            left = mid+1;
    }
    
    return false;
}

int main()
{
    int n;

    while (scanf("%d", &n)!=EOF)
    {
        for (int i = 0; i < n; i++)
        {
            scanf("%d", a+i);
        }
        std::sort(a, a+n);

        int m;
        int t;
        scanf("%d", &m);
        for (int i = 0; i < m; i++)
        {
            scanf("%d", &t);
            bool ans = binSearch(0, n, t);
            if (ans)
                printf("YES\n");
            else
                printf("NO\n");
        }
    }
    
    return 0;
}