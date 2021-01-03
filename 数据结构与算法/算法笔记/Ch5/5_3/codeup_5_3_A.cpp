#include<cstdio>
#include<cstdlib>

typedef long long LL;

struct Fraction
{
    LL up = 0;
    LL down = 1;
};

LL gcd(LL a, LL b)
{
    if (b==0)
        return a;
    else
        return gcd(b, a%b);
}

Fraction reduction(Fraction result)
{
    if (result.down<0)
    {
        result.up = -result.up;
        result.down = -result.down;
    }
    
    if (result.up == 0)
        result.down = 1;
    else
    {
        int d = gcd(abs(result.up), result.down);
        result.up /= d;
        result.down /= d;
    }
    return result;
}

Fraction add(Fraction f1, Fraction f2)
{
    Fraction result;

    result.up = f1.up*f2.down+f2.up*f1.down;
    result.down = f1.down*f2.down;

    return reduction(result);
}

int main()
{
    int N;

    while (scanf("%d", &N)!=EOF && N!=0)
    {
        // Fraction ans;
        // Fraction temp;
        // temp.up = 1;
        // for (int row = 0; row < N; row++)
        // {
        //     for (int col = 0; col < row; col++) //时间复杂度是O(n^2)，会超时
        //     {
        //         temp.down = abs(row-col)+1;
        //         ans = add(ans, temp);
        //     }
        // }
        // ans.up *= 2;
        // ans = reduction(ans);

        // double result = (double)ans.up/ans.down+N;
        // printf("%.2f\n", result);

        double result = .0;
        for (int i = 2; i <= N; i++)
        {
            result += 2*(double)(N-i+1)/i;
        }
        result += 1.0*N;
        printf("%.2f\n", result);
    }
    
    return 0;
}