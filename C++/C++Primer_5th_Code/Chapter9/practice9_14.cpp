#include<iostream>
#include<list>
#include<vector>
#include<string>

int main()
{
    std::list<const char*> l={"Hi",",","LiHua!"};
    std::vector<std::string> v;
    v.assign(l);

    for (auto &&i : v)
    {
        std::cout<<i<<std::endl;
    }
    
    return 0;
}