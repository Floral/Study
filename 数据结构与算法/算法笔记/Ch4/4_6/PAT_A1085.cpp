#include<cstdio>
#include<algorithm>
#define maxn 100005

int arr[maxn] = {0};

int main()
{
    int N, p;

    scanf("%d%d", &N, &p);

    for (int i = 0; i < N; i++)
    {
        scanf("%d", arr+i);
    }

    std::sort(arr, arr+N);

    int i = 0, j = 0;
    int max = 0;
    while (i < N && j < N)
    {
        while (j < N && arr[j]<=(long long)arr[i]*p)
        {
            max = std::max(max, j-i+1);
            j++;
        }
        i++;
    }

    printf("%d\n", max);

    return 0;
}