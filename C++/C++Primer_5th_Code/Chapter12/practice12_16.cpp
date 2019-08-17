#include<iostream>
#include<string>
#include<memory>

int main()
{
    std::unique_ptr<std::string> p1(new std::string("test"));
    // std::unique_ptr<std::string> p2=p1;

    p1.reset(nullptr);
    return 0;
}