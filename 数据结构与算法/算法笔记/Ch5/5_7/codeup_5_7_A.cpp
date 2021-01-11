#include<cstdio>

int exGcd(int a, int b, int &x, int &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    int g = exGcd(b, a%b, x, y);
    int temp = x;
    x = y;
    y = temp - a/b*y;
    return g;
}

int main()
{
    int a, b;
    int x = 0, y = 0;

    while (scanf("%d%d", &a, &b)!=EOF)
    {
        x = 0, y = 0;
        exGcd(a, b, x, y);  //因为题目保证数据一定有解，所以gcd(a, b)一定为1
        while (x<0)
        {
            x+=b;
        }
        printf("%d\n", x);
    }

    return 0;
}