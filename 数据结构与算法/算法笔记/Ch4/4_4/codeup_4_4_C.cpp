#include<cstdio>
#include<algorithm>

struct GasStation
{
    double unitPrice = 0;
    double dis = 0;
} stations[505];

bool hashTable[505] = {false};

bool cmp(GasStation a, GasStation b)
{
    return a.dis < b.dis;
}

int main()
{
    double Cmax, D, Davg;
    int N;
    double curLen = 0, price = 0;
    int curPos = 0, nextPos = 1;
    double C = 0;   //当前油量

    scanf("%lf %lf %lf %d", &Cmax, &D, &Davg, &N);

    for (int i = 0; i < N; i++)
    {
        scanf("%lf %lf", &stations[i].unitPrice, &stations[i].dis);
    }
    //最后一站定为目标城市
    stations[N].unitPrice = 0;
    stations[N].dis = D;
    std::sort(stations, stations+N, cmp);

    // for (int i = 0; i < N+1; i++)
    // {
    //     printf("%d:(%.2lf %.0lf) ", i, stations[i].unitPrice, stations[i].dis);
    // }
    // putchar('\n');
    double dis = Cmax*Davg;
    int lowestPos = nextPos;

    if (stations[0].dis > 0)
    {
        printf("The maximum travel distance = %.2f", curLen);
        return 0;
    }else
    {
        while (curPos < N)
        {
            bool flag = false;  //后面几站是否有加油站比当前的便宜
            // int tempMax = 0;
            if (curLen + dis < stations[curPos+1].dis) //达不到下一个加油站，直接退出
            {
                printf("The maximum travel distance = %.2f", curLen+dis);
                return 0;
            }

            lowestPos = nextPos;
            for (int i = nextPos; i <= N; i++)
            {
                if (curLen + dis < stations[i].dis) //遍历到当前加油站加满油还达不到的范围之外，就跳出
                    break;
                if (stations[i].unitPrice <= stations[lowestPos].unitPrice)
                {
                    lowestPos = i;
                    if (stations[i].unitPrice <= stations[curPos].unitPrice)    //遍历到第一个比当前加油站便宜的就直接跳出
                        break;
                }
            }

            nextPos = lowestPos;
            if (stations[nextPos].unitPrice < stations[curPos].unitPrice)
                flag = true;
            if (flag)   //如果比当前加油站便宜
            {
                C = (stations[nextPos].dis - stations[curPos].dis)/Davg - C;    //在当前站需要加的油量
                price += C*stations[curPos].unitPrice;
                C = 0;  //行驶到下一个加油站之后的油量
            }else
            {
                price += (Cmax - C)*stations[curPos].unitPrice;
                C = Cmax - (stations[nextPos].dis - stations[curPos].dis)/Davg; 
                //行驶到下一个加油站之后的油量
            }
            hashTable[curPos] = true;
            curLen = stations[nextPos].dis;
            curPos = nextPos;
            nextPos = curPos+1;
        }
    }
    printf("%.2f\n", price);
    // for (int i = 0; i < N; i++)
    // {
    //     if (hashTable[i])
    //         printf("%d ", i);
    // }
    
    return 0;
}