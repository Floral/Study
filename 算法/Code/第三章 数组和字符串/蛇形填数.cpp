#include<stdio.h>
#include<string.h>
#define maxm 20
#define maxn 20

int matrix[maxm][maxn];

int main()
{
    int i=1,n;
    int x,y;

    memset(matrix,0,sizeof(matrix)); //矩阵全部置零

    scanf("%d",&n);
    x=0,y=n-1;
    matrix[x][y]=1;
    while(i<n*n)
    {
        /* code */
        while(x<n-1 && !matrix[x+1][y]){
            matrix[++x][y] = ++i;
        }
        while(y>0 && !matrix[x][y-1]){
            matrix[x][--y] = ++i;
        }
        while(x>0 && !matrix[x-1][y]){
            matrix[--x][y] = ++i;
        }
        while(y<n-1 && !matrix[x][y+1]){
            matrix[x][++y] = ++i;
        }
    }
    for(size_t i = 0; i < n; i++)
    {
        /* code */
        for(size_t j = 0; j < n; j++)
        {
            /* code */
            printf("%3d",matrix[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}