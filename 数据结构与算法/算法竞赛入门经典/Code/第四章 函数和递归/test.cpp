#include<stdio.h>

int f(int n)
{
    return n == 0 ?1:f(n-1)*n;
}

int main()
{
    // printf("%d\n",f(3));

    int i=1,j=1,k=100;
    int n=10;
    while (k--)
    {
        /* code */
        printf("%3d,",i);
        i=(i+j+n-1)%n+1;
        if (i%n==1)
        {
            printf("\n");
        }
    }
    
    return 0;
}