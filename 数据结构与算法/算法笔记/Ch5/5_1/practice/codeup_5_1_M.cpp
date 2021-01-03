#include<cstdio>

int main()
{
    int n;
    int a;

    scanf("%d", &n);
    while (n--)
    {
        scanf("%d", &a);

        if (a%2==1)
        {
            printf("0 0\n");
        }else if (a%4!=0)
        {
            printf("%d %d\n", a/4+1, a/2);
        }else
        {
            printf("%d %d\n", a/4, a/2);
        }
    }
    
    return 0;
}