#include<iostream>
#include<cctype>
#include<algorithm>
#include<vector>
// using namespace std;

int main()
{
    std::vector<int> v;    
    std::remove_if(v.begin(),v.end(),ispunct);
    return 0;
}