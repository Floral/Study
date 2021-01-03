#include<cstdio>
#include<algorithm>

int main()
{
    int n;

    while (scanf("%d", &n)!=EOF)
    {
        double money = .0;
        for (int i = 0; i <= 100; i++)
        {
            for (int j = 0; j <= 100-i; j++)
            {
                if ((double)(100-i-j)/3+(double)j*3+(double)i*5 <= n)
                    printf("x=%d,y=%d,z=%d\n", i, j, (100-i-j));
            }
        }
    }
    
    return 0;
}