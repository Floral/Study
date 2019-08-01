#include<stdio.h>
#define maxm 50
#define maxn 50

int matrix[maxm][maxn];

int main()
{
    freopen("data.in","r",stdin);
    int n;
    while(~scanf("%d",&n) && n!=0)
    {
        
        size_t i,flag;
        //input answer
        for(i = 0; i < n; i++)
        {
            scanf("%d",&matrix[0][i]);
        }
        i=0;
        do
        {
            int A=0,B=0,t1=0,t2=0;
            i++;
            flag=0;
            //input guess   
            for(size_t j = 0; j < n; j++)
            {
                scanf("%d",&matrix[i][j]);
                if (matrix[i][j]!=0) {
                    flag=1;
                }
                if (matrix[i][j]==matrix[0][j]) {
                    A++;
                }
                
            }
            for(size_t j = 1; j < 10; j++)
            {
                int c1=0,c2=0;
                for(size_t k = 0; k < n; k++)
                {
                    if (matrix[0][k]==j) {
                        c1++;
                    }
                    if (matrix[i][k]==j) {
                        c2++;
                    }
                }
                B+=(c1>c2?c2:c1);
            }
            
            printf("(%d,%d)\n",A,B-A);

        }while(flag);
        
    }
    
    return 0;
}