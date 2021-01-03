#include<cstdio>
#include<cstring>

int a[2][3] = {0};
int b[3][2] = {0};
int ans[2][2] = {0};

int main()
{
    while (1)
    {
        memset(ans, 0, sizeof(ans));
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (scanf("%d", &a[i][j])==EOF)
                    return 0;
            }
        }
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                scanf("%d",&b[i][j]);
            }
        }

        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                ans[0][i] += a[0][j]*b[j][i];
            }
        }
        
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                ans[1][i] += a[1][j]*b[j][i];
            }
        }

        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                printf("%d ", ans[i][j]);
            }
            putchar('\n');
        }
    }
    
    return 0;
}