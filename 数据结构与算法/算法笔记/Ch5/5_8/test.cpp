#include<cstdio>

int main()
{
    int m[][3]={1,4,7,2,5,8,3,6,9};

    int i, k=2;

    for(i=0;i<3;i++)
        printf("%d",m[k][i]);

    return 0;
}