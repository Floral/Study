#include<cstdio>

int main()
{
    int N;

    while (scanf("%d", &N)!=EOF)
    {
        int t;
        int max, min;
        scanf("%d", &t);
        max = min = t;
        for (int i = 1; i < N; i++)
        {
            scanf("%d", &t);
            if (t > max)
                max = t;
            else if (t < min)
                min = t;
        }
        printf("%d %d\n", max, min);
    }
    
    return 0;
}