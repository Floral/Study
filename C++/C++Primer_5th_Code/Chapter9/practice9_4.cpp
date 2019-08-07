#include<iostream>
#include<vector>

using std::vector;
using std::cin; using std::cout; using std::endl;

bool find(vector<int>::iterator b, vector<int>::iterator e, int target)
{
    while (b!=e)
    {
        if (*b==target)
        {
            return true;
        }
        ++b;
    }
    return false;
}

int main()
{

    return 0;
}