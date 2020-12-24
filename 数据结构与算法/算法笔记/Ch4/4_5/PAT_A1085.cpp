#include<cstdio>
#include<algorithm>
#define maxn 100005

int arr[maxn] = {0};

int findGreaterThanX(int left, int right, long long x)
{
    int mid;
    while (left+1 < right)
    {
        mid = (left+right)/2;
        if (arr[mid] > x)
            right = mid;
        else
            left = mid;
    }

    return right;
}

int main()
{
    int N, p;

    scanf("%d%d", &N, &p);

    for (int i = 0; i < N; i++)
    {
        scanf("%d", arr+i);
    }

    std::sort(arr, arr+N);

    int ans, max = 0;

    for (int i = 0; i < N; i++)
    {
        ans = findGreaterThanX(i, N, (long long)arr[i]*p);
        if (ans-i >= max)
            max = ans-i;
    }
    printf("%d\n", max);
    
    return 0;
}