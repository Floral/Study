#include<cstdio>
#include<algorithm>
#define maxn 110

struct Interval
{
    int x, y;
} I[maxn];

bool hashTable[maxn] = {false};

bool cmp(Interval a, Interval b)    //只有cpp可以这样写,c需要写成struct Interval
{
    if (a.x!=b.x)
        return a.x > b.x;
    else
        return a.y < b.y;
}

int main()
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &I[i].x, &I[i].y);
    }

    std::sort(I, I+n, cmp);
    int lastX = I[0].x;
    printf("(%d, %d) ", I[0].x, I[0].y);

    for (int i = 1; i < n; i++)
    {
        if (I[i].y <= lastX)
        {
            lastX = I[i].x;
            printf("(%d, %d) ", I[i].x, I[i].y);
        }
    }
    
    return 0;
}