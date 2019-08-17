#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include"StrBlob.h"
// #include"StrBlobPtr.h"

using namespace std;

int main()
{
    StrBlob sb;
    std::string s;
    std::ifstream ifs("data.in");
    while (std::getline(ifs,s))
    {
        sb.push_back(s);
    }
    
    StrBlobPtr sbp(sb);
    for (int i=0;i<sb.size() ;++i )
    {
        std::cout<<sbp.deref()<<std::endl;
        sbp.incr();
    }
    // std::cout<<std::endl;

    return 0;
}