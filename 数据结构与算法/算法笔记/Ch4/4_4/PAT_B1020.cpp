#include<cstdio>
#include<algorithm>
#define N 1005

typedef struct mooncake
{
    double num;
    double unitPrice;
}mc;

mc myMc[N];

double solution(int n, double sum, mc* myMc)
{
    double ans = 0;
    for (int i = 0; i < n; i++)
    {
        if (sum-myMc[i].num>=0) //sum是剩余的数量
        {
            sum -= myMc[i].num;
            ans += (myMc[i].num*myMc[i].unitPrice);
        }else
        {
            ans += (myMc[i].unitPrice*sum);
            sum = 0;
            break;
        }
    }
    
    return ans;
}

bool cmp(const mc &a, const mc &b)
{
    return a.unitPrice>b.unitPrice;
}

int main()
{
    int n;
    double sum;
    int i;
    scanf("%d %lf", &n, &sum);

    for (i = 0; i < n; i++)
    {
        scanf("%lf", &myMc[i].num);
    }

    double temp;
    for (i = 0; i < n; i++)
    {
        scanf("%lf", &temp);
        myMc[i].unitPrice = temp/myMc[i].num;
    }

    std::sort(myMc, myMc+n, cmp);
    double ans = solution(n, sum, myMc);
    printf("%.2f\n", ans);

    return 0;
}