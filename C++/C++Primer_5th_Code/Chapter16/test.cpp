#include<iostream>
#include<string>

template<typename T>
int compare(T a, T b)
{
    if(a<b)
        return -1;
    if(b<a)
        return 1;
    return 0;
}

int main()
{
    std::cout<<compare(1,0)<<std::endl;
    return 0;
}