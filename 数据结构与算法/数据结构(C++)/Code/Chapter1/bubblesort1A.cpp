#include<iostream>
#define __int64 long long 

using namespace std;

void test(int n)
{
    ne:
        if(1<n--){
            goto ne;
        }
        
}
int fib(int n)
{
    int f=0,g=1;
    while(0<n--){
        g+=f;
        f=g-f;
    }
    return f;
}

int main()
{
    __int64 a=2;
    printf("%d",fib(6));
    return 0;
}