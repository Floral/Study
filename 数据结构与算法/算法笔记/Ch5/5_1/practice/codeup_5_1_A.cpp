#include<cstdio>
#include<cmath>

bool judge(int N)
{
    bool ans = false;

    if (N>=10)
    {
        if ((N*N)%100 == N)
            ans = true;
    }else
    {
        if ((N*N)%10 == N)
            ans = true;
    }
    return ans;
}

int main()
{
    int N;
    
    while (scanf("%d", &N)!=EOF)
    {
        if (judge(N))
            printf("Yes!\n");
        else
            printf("No!\n");
    }
    
    return 0;
}