#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<set>
#include<stack>
#include<algorithm>
#define ALL(x) x.begin(),x.end()
#define INS(x) inserter(x,x.begin())

using namespace std;
typedef set<int> Set;
stack<int> s;
map<Set,int> IDcache;
vector<Set> Setcache;

int ID(Set x)
{
    if (IDcache.count(x))
        return IDcache[x];

    Setcache.push_back(x);
    
    return IDcache[x]=Setcache.size()-1;
}


int main()
{
    /* 
    set<int> x1;
    set<int> x2;
    set<int> x3;
    set<int> x4;
    map<set<int>,int> t;
    vector<set<int>> v;
    v.push_back(x1);
    v.push_back(x2);
    t[x1]=0;
    t[x2]=1;
    t[x4]=4;
    cout<<t[x3]<<endl;
    cout<<v<<endl;
    */
    int t,n;
    cin>>t;
    while (t--)
    {
        cin>>n;
        while (n--)
        {
            string op;
            cin>>op;
            if (op[0]=='P')
                s.push(ID(Set()));
            else if(op[0]=='D')
                s.push(s.top());
            else
            {
                Set x1 = Setcache[s.top()]; s.pop();
                Set x2 = Setcache[s.top()]; s.pop();
                Set x;
                if (op[0]=='U') set_union(ALL(x1),ALL(x2),INS(x));
                if (op[0]=='I') set_intersection(ALL(x1),ALL(x2),INS(x));
                if (op[0]=='A') {x=x2; x.insert(ID(x1));}
                s.push(ID(x));
            }
            cout<<Setcache[s.top()].size()<<endl;
        }
        cout<<"***"<<endl;
    }
    

    return 0;
}