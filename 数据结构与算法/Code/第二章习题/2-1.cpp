#include<stdio.h>

int power(int x,int y)
{
    int result=1;

    while(y>0){
        /* code */
        result*=x;
        y--;
    }
    return result;
}

int main()
{
    for(int i = 100; i < 1000; i++)
    {
        /* code */
        
        int x,y,z;
        x=i/100;
        y=i/10%10;
        z=i%10;
        if (i== power(x,3)+power(y,3)+power(z,3)){
            /* code */
            printf("%d\n",i);
        }
    }

    return 0;
}