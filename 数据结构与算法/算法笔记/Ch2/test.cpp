#include<stdio.h>
#include<string.h>

#define ADD(a, b) (a+b)

int main()
{
    int num1 = 1, num2 = 2;
    printf("%d\n", ADD(num1, num2*2+1));

    int a[5];
    memset(a, 1, sizeof(a));
    for (auto &i : a)
    {
        printf("%d ", i);
    }
    
    return 0;
}