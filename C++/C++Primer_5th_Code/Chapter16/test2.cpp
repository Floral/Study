#include<iostream>
#include<string>
#include<vector>

using namespace std;

template<typename It>
auto fcn(It beg, It end) ->
    typename remove_reference<decltype(*beg)>::type
{
    for(; beg!=end; ++beg)
    {
        if (*beg=="bye")
        {
            return *beg;
        }
    }
    return "";
}

int main()
{
    vector<string> v{"1","2","3","hhhh"};

    auto s = fcn(v.begin(), v.end());

    cout<<s<<endl;
    return 0;
}