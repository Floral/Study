#include<cstdio>
#include<cmath>
#define maxn 100000

struct Factor
{
    int x, cnt;
};

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

Factor factors[10];
int num = 0;

void PrimeFactor(int n)
{
    int sqr = (int)sqrt(1.0*n);

    for (int i = 0; prime[i] < sqr; i++)
    {
        if (n%prime[i] == 0)
        {
            factors[num].x = prime[i];
            factors[num].cnt = 0;
            while (n%prime[i]==0)
            {
                ++factors[num].cnt;
                n/=prime[i];
            }
            ++num;
        }
    }

    if (n>1)
    {
        factors[num].x = n;
        factors[num].cnt = 1;
        ++num;
    }
}

int main()
{
    int N;
    
    scanf("%d", &N);
    if (N==1)
    {
        printf("1=1");
        return 0;
    }

    Find_Prime();
    PrimeFactor(N);

    printf("%d=", N);
    for (int i = 0; i < num; i++)
    {
        printf("%d", factors[i].x);
        if (factors[i].cnt>1)
            printf("^%d", factors[i].cnt);
        if (i<num-1)
            putchar('*');
    }

    return 0;
}