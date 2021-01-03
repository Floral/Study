#include<cstdio>
#define maxn 100001

int prime[maxn] = {0};
bool p[maxn] = {false};
int pNum = 0;

void Find_Prime()
{
    for (int i = 2; i < maxn; i++)
    {
        if (p[i] == false)
        {
            prime[pNum++] = i;
            for (int j = i+i; j < maxn; j+=i)
            {
                p[j] = true;
            }
        }
    }
}

int findPos(int n)
{
    int pos = 0;
    while (prime[pos]<n)
        pos++;
    return pos-1;
}

int main()
{
    Find_Prime();

    int n;
    while (scanf("%d", &n)!=EOF && n!=0)
    {
        int num = 0;
        int i = 0, j = findPos(n);

        while (i<=j)
        {
            if (prime[i]+prime[j] == n)
            {
                ++num;
                ++i;
                --j;
            }else if (prime[i]+prime[j] < n)
                ++i;
            else
                --j;
        }
        
        printf("%d\n", num);
    }
    
    return 0;
}