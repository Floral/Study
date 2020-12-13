#include<cstdio>
#define maxn 20

int seq[maxn] = {0};

void fibo(int n)
{
    for (size_t i = 1; i <= n; i++)
    {
        if (i == 1 || i == 2)
            seq[i] = 1;
        else
            seq[i] = seq[i-1] + seq[i-2];
    }
}

int main()
{
    int m, n;

    scanf("%d", &m);
    fibo(2*(10-1)+1);
    while (m--)
    {
        scanf("%d", &n);
        
        // fibo(2*(n-1)+1);
        for (size_t i = 1; i <= n; i++)
        {
            for (size_t j = 0; j < 2*(n-i); j++)
            {
                printf(" ");
            }
            for (size_t k = 0; k < 2*(i-1)+1; k++)
            {
                printf("%d", seq[k]);
                if (k!=2*(i-1))
                {
                    printf(" ");
                }
            }
            printf("\n");
        }
    }

    return 0;
}