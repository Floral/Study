#include<iostream>
#include<algorithm>
#include<vector>
#include<string>

const int maxn = 30;
using namespace std;
int n;
vector<int> pile[maxn];

void find_block(int i,int &p,int &h)
{
    for (p = 0; p < n; ++p)
    {
        for (h = 0; h < pile[p].size(); ++h)
        {
            if (i==pile[p][h])
            {
                return;
            }
        }
    }
}

void clear_blocks(const int &p, const int &h)
{
    for (size_t i=h+1; i < pile[p].size(); ++i)
    {
        int t = pile[p][i];
        pile[t].push_back(t);
    }
    pile[p].resize(h+1);
}

void pile_blocks(const int &p, const int &h,const int &p2)
{
    for (size_t i = h; i < pile[p].size(); ++i)
    {
        int t = pile[p][i];
        pile[p2].push_back(t);
    }
    pile[p].resize(h);
}

void print()
{
    for (size_t i = 0; i < n; i++)
    {
        printf("%d:",i);
        for (auto &j : pile[i])
        {
            printf(" %d",j);
        }
        printf("\n");
    }
}

int main()
{
    string s1,s2;

    int a,b;
    a=b=0;
    cin >> n;
    for (size_t i = 0; i < n; i++)
    {
        pile[i].push_back(i);
    }
    
    while (cin>>s1>>a>>s2>>b)
    {
        int p1=0,h1=0;
        int p2=0,h2=0;

        find_block(a,p1,h1);
        find_block(b,p2,h2);
        // cout<<"pa:"<<p1<<" ha:"<<h1<<endl;
        // cout<<"pb:"<<p2<<" hb:"<<h2<<endl;
        // cout<<"s1:"<<s1<<" s2:"<<s2<<endl;
        if (p1==p2)
        {continue;}
        if (s1=="move")
        {
            clear_blocks(p1,h1);
        }
        if (s2=="onto")
        {
            clear_blocks(p2,h2);
        }
        pile_blocks(p1,h1,p2);
        // print();
    }
    print();    
    return 0;
}