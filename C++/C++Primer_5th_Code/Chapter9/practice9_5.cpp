#include<iostream>
#include<vector>

using std::vector;
using std::cin; using std::cout; using std::endl;

vector<int>::iterator find(vector<int>::iterator b, vector<int>::iterator e, int target)
{
    while (b < e)
    {
        if (*b==target)
        {
            return b;
        }
        ++b;
    }
    return e;
}

int main()
{

    return 0;
}