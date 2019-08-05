#include<iostream>
#include<fstream>
#include<string>

int main()
{
    std::ifstream fs("chinese-3500.txt");
    std::string s;
    // getline(fs,s);    
    for (size_t i = 0; i < 100; i++)
    {
        /* code */
        fs >> s;
    std::cout<<s<<std::endl;
    }
    // std::cout<<s<<std::endl;
    return 0;
}