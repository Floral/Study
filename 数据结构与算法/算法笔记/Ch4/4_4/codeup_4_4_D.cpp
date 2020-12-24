#include<cstdio>
#include<algorithm>
#define maxn 605
int arr[maxn] = {0};
bool cmp(int a, int b)
{
    return a > b;
}

int main()
{
    int L, N;
    while (scanf("%d %d", &L, &N)!=EOF)
    {
        int t = 0, i;
        for (i = 0; i < N; i++)
        {
            scanf("%d", arr+i);
        }
        std::sort(arr, arr+N, cmp);

        for (i = 0; i < N; i++)
        {
            t += arr[i];
            if (t >= L)
                break;
        }
        if (i < N)
            printf("%d\n", i+1);
        else
            printf("impossible\n");
    }
    return 0;
}