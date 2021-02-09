#include<cstdio>

//* 超时
// int solve(int m, int n)
// {
//     if (m>n)
//         return 0;
    
//     int sumLeft = solve(m*2, n);
//     int sumRight = solve(m*2+1, n);
    
//     return 1+sumLeft+sumRight;
// }

int solve(int m, int n)
{
    if (m>n)
        return 0;
    int t = m;
    int level = 0;
    int sum = 1;
    int i = 1;
    while ((m<<1)+1 <= n)   //* 判断能加多少个完整的层
    {
        ++level;
        i <<= 1;
        sum += i;
        m = (m<<1)+1;
    }
    t <<= (level+1);
    // while (t<=n)
    // {
    //     ++sum;
    //     ++t;
    // }
    // int left = (t<=n)?(n-t+1):0;
    sum = sum + ((t<=n)?(n-t+1):0);     //* 加剩下的不完整的一层
    //! 后面一部分不加括号会出bug,原因是三目运算符会把前面的sum+(t<=n)当作判断条件

    return sum;
}

int main()
{
    int m, n;
    while (scanf("%d %d", &m, &n)!=EOF && (m!=0 && n!=0))
    {
        printf("%d\n", solve(m, n));
    }
    return 0;
}