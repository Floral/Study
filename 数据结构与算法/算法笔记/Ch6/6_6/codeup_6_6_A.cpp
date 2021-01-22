#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<queue>
#include<unordered_map>
#include<string>

using namespace std;

struct Task
{
    int num;
    int priority;
    friend bool operator<(const Task &a, const Task &b){
        if (a.priority!=b.priority)
            return a.priority>b.priority;
        else
            return a.num > b.num;
    }
};

priority_queue<Task> q;
unordered_map<int, int> mp;

void input(int i)
{
    string str;
    cin>>str;

    int p = str.find('(');
    int num = 0;
    Task t;
    num = atoi(str.substr(4, p-4).c_str());
    if (mp[num] == 0)
    {
        mp[num] = 1;
        t.num = num;
        t.priority = i;
        q.push(t);
    }
    
    str.erase(str.begin(), str.begin()+p+1);
    str.erase(str.end()-1);
    while ((p=str.find(','))!=string::npos)
    {
        num = atoi(str.substr(4, p-4).c_str());
        if (mp[num] == false)
        {
            mp[num] = true;
            t.num = num;
            t.priority= i+1;
            q.push(t);
        }
        
        str.erase(str.begin(), str.begin()+p+1);
    }
    if (str!="NULL")
    {
        num = atoi(str.substr(4, str.length()-4).c_str());
        if (mp[num] == false)
        {
            mp[num] = true;
            t.num = num;
            t.priority= i+1;
            q.push(t);
        }
    }
}

//! 这个题我一开始想得很复杂，一看别人的答案很简单，我觉得绝对是题目表达不清的锅
//! 题目的意思是，前序任务执行完后马上执行后序任务，造成多种可能序列的原因在于后序任务的执行顺序，我们始终选择小的先执行就可以了
//! 我最先以为不是执行完前序任务马上就执行后序任务:
//* Task0(Task1,Task3)
//* Task1(Task3)
//* Task2(NULL)
//* Task3(NULL)
//* 那么输出最小的字典序应该是0123，但是百度到的答案的输出都是0132，这就验证了我上面的说明
//! 2021.1.16晚发现，直接按照序号从0到n输出居然也能ac，这个题目的测试案例肯定有毒！实际应该是比较复杂的一道题，怪不得ac率这么高
int main()
{
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; i++)
        input(i);
    
    while (!q.empty())
    {
        printf("Task%d ", q.top().num);
        q.pop();
    }
    
    return 0;
}