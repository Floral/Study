#include<iostream>
#include<memory>
#include<string>

using std::string;
using std::cin; using std::cout; using std::allocator;
using std::endl;

int main()
{
    allocator<string> a;
    int n;

    cout<<"please input how many strings do you want to allocate?"<<endl;
    cin>>n;
    auto const p = a.allocate(n);
    auto q = p;
    string s;
    cout<<"please input:"<<endl;
    while (cin>>s && q!=p+n)
    {
        a.construct(q++,s);
    }
    
    auto t = p;
    while (t!=q)
    {
        cout<<(*t)<<endl;
        ++t;
    }
    
    while (q!=p)
    {
        a.destroy(--q);
    }
    a.deallocate(p,n);

    return 0;
}