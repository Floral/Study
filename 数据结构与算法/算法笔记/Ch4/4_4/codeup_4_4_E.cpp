#include<cstdio>
#include<algorithm>
#define maxn 1005

struct Room
{
    int J;
    int F;
}rooms[maxn];

bool cmp(Room a, Room b)
{
    return ((double)a.J/(double)a.F) > ((double)b.J/(double)b.F);
}

int main()
{
    double M;
    int N;
    double ans = 0;

    while (scanf("%lf %d", &M, &N)!=EOF)
    {
        ans = 0;
        if (M == -1 && N == -1)
            break;
        
        for (int i = 0; i < N; i++)
        {
            scanf("%d %d", &rooms[i].J, &rooms[i].F);
        }
        std::sort(rooms, rooms+N, cmp);

        for (int i = 0; i < N && M > 0; i++)
        {
            if (rooms[i].F < M)
            {
                M -= rooms[i].F;
                ans += rooms[i].J;
            }else
            {
                ans += M*(double)rooms[i].J/(double)rooms[i].F;
                M = 0;
            }
        }
        printf("%.3lf\n", ans);
    }

    return 0;
}