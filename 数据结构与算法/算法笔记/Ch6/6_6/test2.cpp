#include<stdio.h>
#include<algorithm>
#include<iostream>
#include<queue>
#include<map>
using namespace std;
int n;
struct task
{
    string name;
    int priority;
    friend bool operator<(const task &t1, const task &t2)
    {
        if(t1.priority!=t2.priority)
            return t1.priority > t2.priority;//输出优先级大的
        else
            return t1.name > t2.name;//输出字典序小的
    }
};
void deal(string s, priority_queue<task> &p, map<string, int> &list)
{
    string now = "";
    task t;
    int i=0;
    //处理第一个
    while(s[i]!='(')
    {
        now+=s[i];
        i++;
    }
    if(list[now]==0)//第一个
    {
        t.name = now;
        t.priority = 0;
        list[now] = 0;
        p.push(t);
    }
    s.erase(s.begin(), s.begin()+i);//删除Task0
    s.erase(s.begin());//删除(
    int temp = list[now]+1;
    i=0;
    now = "";
 
 
    //处理括号里面的
    while(i<s.size())
    {
        if((s[i]==','||s[i]==')')&&list[now]==0&&now!="NULL")
        {
            t.name = now;
            t.priority = temp;
            list[now] = temp;
            p.push(t);
            //cout<<now<<" "<<temp <<endl;
            now = "";
        }
        else
            now+=s[i];
        i++;
    }
}
int main()
{
 
    while(scanf("%d",&n)!=EOF)
    {
        priority_queue<task> p;
        map<string, int> list;//名字---优先级
        for(int i=0; i<n; i++)
        {
            string s;
            cin>>s;
            deal(s, p, list);
        }
        while(p.empty()!=1)
        {
            cout<<p.top().name;
            if(p.size()>1)
                cout<<" ";
            else
                cout<<endl;
            p.pop();
        }
    }
    return 0;
}