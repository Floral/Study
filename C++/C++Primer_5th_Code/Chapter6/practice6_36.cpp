#include<iostream>
#include<string>

using std::string;

string (&func(int i))[10];

int a;
int b(1);


int* reset(int*);
double* reset(double*,int a= b);

constexpr int test(int a)
{
    return 8*a;
}

int main()
{
    std::cout<<b<<std::endl;
    int i;
    std::cin>>i;
    std::cout<<test(i)<<std::endl;
    return 0;
}