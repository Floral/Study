#include<stdio.h>
#include<algorithm>
 
using namespace std;
 
struct Program
{
    int s, e;
} programs[105];

bool hashTable[105] = {false};
 
bool cmp(Program a, Program b)
{
    if(a.s!=b.s)
        return a.s > b.s;
    else
        return a.e < b.e;
}
 
int main()
{
 
    int n;
    while (scanf("%d",&n), n!=0)
    {
        for (size_t i = 0; i < n; ++i)
        {
            scanf("%d %d", &programs[i].s, &programs[i].e);
        }
        sort(programs, programs+n, cmp);
        int ans = 1, lastS = programs[0].s;
        hashTable[0] = true;
        for (size_t i = 1; i < n; ++i)
        {
            if (programs[i].e <= lastS)
            {
                hashTable[i] = true;
                lastS = programs[i].s;
                ++ans;
            }
        }

        printf("%d:\n", ans);

        for (int i = 0; i < n; i++)
        {
            if (hashTable[i])
            {
                printf("(%d, %d) ", programs[i].s, programs[i].e);
            }
        }
        putchar('\n');
    }
     
    return  0;
}