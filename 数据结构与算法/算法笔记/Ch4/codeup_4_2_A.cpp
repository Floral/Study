#include<cstdio>
#include<cstring>
#define maxn 210

// int mat[maxn] = {0};
// int person[maxn] = {0};

int main()
{
    int N,M;
    // int temp;

    while (scanf("%d %d", &N, &M)!=EOF)
    {
        int mat[maxn] = {0};       //书每次要重置,不然会累加
        int person[maxn] = {0};
        for (size_t i = 0; i < N; i++)
        {
            scanf("%d", person+i);
            mat[person[i]]++;
        }
        
        for (size_t i = 0; i < N; i++)
        {
            if (mat[person[i]] == 1)
            {
                printf("BeiJu\n");
            }else
            {
                printf("%d\n",mat[person[i]]-1);
            }
        }
    }
    
    return 0;
}