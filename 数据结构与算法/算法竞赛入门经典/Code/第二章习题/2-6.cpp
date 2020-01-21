#include<stdio.h>

int judge(int a,int b,int c)
{
    int t[9];
    int x=a*1000000+b*1000+c;
    for(int i = 0; i < 9; i++)
    {
        /* code */
        t[i]=x%10;
        x=x/10;
        if (t[i]==0) {
            /* code */
            return 0;
        }
        
    }

    for(int i = 0; i < 9; i++)
    {
        /* code */
        for(int j = i+1; j < 9; j++)
        {
            /* code */
            if (t[i]==t[j]) {
                /* code */
                return 0;
            }
        }
    }

    return 1;
}

int main()
{
    for(int i = 123; i < 334; i++)
    {
        /* code */
        int j=i*2,k=i*3;
                /* code */
        if (judge(i,j,k)) {
                    /* code */
            printf("%d %d %d\n",i,j,k);
        }
        
    }
    return 0;
}