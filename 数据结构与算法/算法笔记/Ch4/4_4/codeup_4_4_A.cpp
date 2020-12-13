#include<cstdio>
#include<algorithm>
#define maxn 105
using namespace std;

struct Program
{
    int si, ei;

} p[maxn];

bool hashTable[maxn] = {false};

bool cmp(Program a, Program b)
{
    if (a.ei!=b.ei)
        return a.ei < b.ei;
    else
        return a.si < b.si;
}

int main()
{
    int n;

    while (scanf("%d", &n) && n!=0)
    {
        for (int i = 0; i < n; i++)
        {
            scanf("%d %d", &p[i].si, &p[i].ei);
        }
        sort(p, p+n, cmp);
        int ans = 1;
        int lastEi = p[0].ei;
        
        hashTable[0] = true;
        
        for (int i = 1; i < n; i++)
        {
            if (p[i].si >= lastEi)
            {
                lastEi = p[i].ei;
                hashTable[i] = true;
                ans++;
            }
        }
        printf("%d:\n", ans);
        
        for (int i = 0; i < n; i++)
        {
            if (hashTable[i])
            {
                printf("(%d, %d) ", p[i].si, p[i].ei);
            }
        }
        putchar('\n');
    }

    return 0;
}