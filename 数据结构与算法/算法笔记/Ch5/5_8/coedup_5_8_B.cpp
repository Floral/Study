#include<cstdio>

double fact(int m, int n)   //从m个中选n个
{
    double ans = 1;

    for (int i = 1; i <= n; i++)
    {
        ans = ans*(m-n+i)/i;
    }

    return ans;
}

int main()
{
    int m, n;
    while (scanf("%d%d", &m, &n)!=EOF)
    {
        double ans = fact(m, n);
        printf("%.0f\n", ans);
    }

    return 0;
}