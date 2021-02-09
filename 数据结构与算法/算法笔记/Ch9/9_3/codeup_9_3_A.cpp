#include<cstdio>
#include<cstring>
#define maxn 1005

int tree[maxn] = {0};

void levelTravel(int d, int n)
{
    if ((1<<(d-1))>n)
    {
        printf("EMPTY\n");
        return ;
    }
    for (int i = (1<<(d-1)); i<n && i<(1<<d); i++)
    {
        if (i!=(1<<(d-1)))
            printf(" ");
        printf("%d", i);
    }
    putchar('\n');
}

int main()
{
    int n;
    while (scanf("%d", &n)!=EOF && n!=0)
    {
        int d;
        memset(tree, 0, sizeof(tree));
        for (int i = 0; i < n; i++)
        {
            scanf("%d", tree+i);
        }
        scanf("%d", &d);
        levelTravel(d, n);
    }
    
    return 0;
}