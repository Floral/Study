#include<cstdio>
#include<cmath>
#define maxn 1000000

bool isPrime(int n)
{
    if (n<=1)
        return false;
    
    int sqr = (int)sqrt(1.0*n);
    for (int i = 2; i <= sqr; i++)
    {
        if (n%i==0)
            return false;
    }
    return true;
}

int prime[maxn] = {0};
bool p[maxn] = {false};
int pNum = 0;

void Find_Prime()
{
    for (int i = 2; i < maxn; i++)
    {
        if (p[i] == false)
        {
            // printf("%d ", pNum);
            prime[pNum++] = i;
            // printf("%d\n", prime[pNum-1]);
            for (int j = i+i; j < maxn; j+=i)   //! BUG 这里最好不要写成小于等于maxn的条件，否则会因为超出p的数组界限而改变pNum的值，而造成bug
            {
                p[j] = true;
            }
        }        
    }
}

int main()
{
    int M, N;
    Find_Prime();
    
    scanf("%d%d", &M, &N);

    int count = 0;
    for (int i = M-1; i < N; i++)
    {
        printf("%d", prime[i]);
        if ((++count)%10==0 || i == N-1)
            putchar('\n');
        else
            putchar(' ');
    }

    return 0;
}