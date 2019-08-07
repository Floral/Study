#include<iostream>
#include<list>
#include<deque>
#include<string>
#include<vector>

int main()
{
    std::list<std::deque<int>> test;
    std::string s="abcd";
    for (auto &i : s)
    {
        std::cout<<i<<std::endl;
    }
    std::vector<std::string> v;
    v.emplace_back("dsada");
    for (auto &i : s)
    {
        std::cout<<i<<std::endl;
    }
    return 0;
}