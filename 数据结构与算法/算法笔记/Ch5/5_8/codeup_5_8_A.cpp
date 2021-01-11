#include<cstdio>
#define maxn 1001

int res[maxn][maxn] = {0};

void fact()
{
    // int ans;
    for (int i = 0; i < maxn; i++)
        res[i][0] = res[i][i] = 1;

    for (int i = 2; i < maxn; i++)
    {
        for (int j = 1; j <= i/2; j++)
        {
            res[i][j] = res[i-1][j] + res[i-1][j-1];
            res[i][i-j] = res[i][j];
        }
    }
    // return ans;
}

int main()
{
    int m, n;

    fact();
    while (scanf("%d%d", &m, &n)!=EOF)
    {
        printf("%d\n",res[m][n]);
    }

    return 0;
}