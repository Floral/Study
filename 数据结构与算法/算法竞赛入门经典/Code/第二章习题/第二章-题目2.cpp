#include<stdio.h>

int main()
{
    double i;
    for( i = 0; i != 10.0; i+=0.1)
    {
        /* code */
        printf("%.1f\n",i);
    }
    return 0;
}