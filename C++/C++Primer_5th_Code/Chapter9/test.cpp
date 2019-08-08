#include<iostream>
#include<list>
#include<deque>
#include<string>
#include<vector>

int main()
{
    /* 
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
    */
    std::vector<int> ivec;

    std::cout<<"ivec:size: "<<ivec.size()
                <<" capacity: "<<ivec.capacity()<<std::endl;

    ivec.reserve(20);
    std::cout<<"ivec:size: "<<ivec.size()
                <<" capacity: "<<ivec.capacity()<<std::endl;


    ivec.shrink_to_fit();
    std::cout<<"ivec:size: "<<ivec.size()
                <<" capacity: "<<ivec.capacity()<<std::endl;
    return 0;
}