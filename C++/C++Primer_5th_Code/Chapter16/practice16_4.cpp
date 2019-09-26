#include<iostream>
#include<string>
#include<vector>
#include<list>

using std::cout; using std::cin; using std::endl;
using std::vector;
using std::string;
using std::list;

template<typename Iterator, typename valuetype>
Iterator search(Iterator beg, Iterator end, const valuetype& val)
{
    while (beg!=end && *beg!=val)
    {
        ++beg;
    }
    return beg;
}

int main()
{
    vector<int> v{1,2,3,4,5,6,7,8,9,0};
    vector<int>::iterator it=search(v.begin(),v.end(),6);
    cout<<*it<<endl;
    return 0;
}
