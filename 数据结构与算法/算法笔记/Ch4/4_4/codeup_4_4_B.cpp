#include<cstdio>

double solution(int n)  //方案2
{
    double ans = 0;
    bool flag = true; //是否是一开始就小于4km

    if (n >= 8)
    {
        flag = false;
        ans += ((n/8)*18);  //先直接取8的整数倍
        n %= 8;
    }

    //再判断剩余的公里数
    if (n > 4)  //超过4的直接坐下一辆
    {
        ans += (10+(n-4)*2);
        n = 0;
    }else if (flag) //没有超过4，需要看是不是一开就是不超过4，是的话，只能坐一辆
    {
        ans += 10;
        n = 0;
    }else   //不是的话可以继续坐上一辆
    {
        ans += 2.4*n;
        n = 0;
    }

    return ans;
}


int main()
{
    int n;

    while (scanf("%d", &n)!=EOF && n!=0)
    {
        double price = 0;

        // while (n!=0)
        // {
        //     if (n>13)       //超过13(8+5)公里肯定得做下一辆车
        //     {
        //         price += 18;
        //         n -= 8;
        //     }else if (n>8)  //超过8公里不到13的,继续坐完
        //     {
        //         price += (18+2.4*(n-8));
        //         n = 0;
        //     }else if (n>4)  //超过4公里不到8公里的也继续坐完
        //     {
        //         price += (10+2*(n-4));
        //         n = 0;
        //     }else if (n<=4) //不到4公里的
        //     {
        //         price += 10;
        //         n = 0;
        //     }
        // }
        price = solution(n);

        if ((price-(int)price)==0)
            printf("%d\n",(int)price);
        else
            printf("%.1lf\n", price);
    }

    return 0;
}