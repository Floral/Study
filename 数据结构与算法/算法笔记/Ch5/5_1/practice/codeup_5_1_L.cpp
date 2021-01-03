#include<cstdio>

bool related2seven(int x)
{
    if (x%7==0)
        return true;
    while (x!=0)
    {
        if (x%10==7)
            return true;
        x/=10;
    }
    return false;
}

int main()
{
    int n, ans;

    while (scanf("%d", &n)!=EOF)
    {
        ans = 0;
        for (int i = 1; i <= n; i++)
        {
            if (!related2seven(i))
                ans += (i*i);
        }
        printf("%d\n", ans);
    }
    
    return 0;
}