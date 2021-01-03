#include<cstdio>
#define maxn 10001

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

int main()
{
    Find_Prime();

    int n;
    while (scanf("%d", &n)!=EOF)
    {
        bool flag = false;
        for (int i = 0; i < pNum; i++)
        {
            if (prime[i] >= n)
                break;
            
            if (prime[i]%10 == 1)       //* 也可以直接把这个判断放在Find_Prime中向prime添加质数之前
            {
                if (flag)
                    putchar(' ');
                
                printf("%d", prime[i]);
                flag = true;
            }
        }
        if (!flag)
        {
            printf("-1");
        }
        putchar('\n');
    }
    
    return 0;
}