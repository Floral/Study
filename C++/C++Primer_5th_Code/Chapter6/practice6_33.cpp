#include<iostream>
#include<vector>

using std::cin; using std::cout;
using std::endl;using std::vector;

void fac(const vector<int> &v,int i)
{
    if (i> -1)
    {
        cout<<v[i]<<endl;
        fac(v,i-1);
    }
    else
    {
        return;
    }
}

int main()
{
    vector<int> v{1,2,3,4,5,6,7,8,9,0};
    int i=10;
    fac(v,9);
    return 0;
}