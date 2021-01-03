#include<cstdio>

int main()
{
    double x, y;
    int n;

    while (scanf("%lf %d", &x, &n)!=EOF)
    {
        y = x;
        for (int i = 0; i < n; i++)
        {
            y = y*2/3+x/(3*y*y);
        }
        printf("%.6f\n", y);
    }
    
    return 0;
}