#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

class Equals{
public:
    Equals(int value=0):value(value){};
    bool operator()(const int x)
    {
        return x==value;
    }

private:
    int value;
};

int main()
{
    vector<int> v{1,2,3,4,5,6,7,7,8,2,0};

    replace_if(v.begin(),v.end(),Equals(7),99);
    for (auto &&i : v)
    {
        cout<<i<<" ";
    }
    cout<<endl;
    return 0;
}