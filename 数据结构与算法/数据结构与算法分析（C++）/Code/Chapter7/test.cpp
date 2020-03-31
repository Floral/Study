#include<iostream>
#include"QuickSort.h"

using namespace std;

int main()
{
    vector<int> a{1,44,74,21,6,21,6,26,89,4,352,13,4,68,25};

    cout<<"a.size() : "<<a.size()<<endl;
    quickSort(a);

    for (auto &&i : a)
        cout<<i<<" ";
    
    return 0;
}