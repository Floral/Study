#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<map>

using namespace std;

vector<string> deal(string s)
{
    vector<string> vs;
    //除去无意义前缀
    for (auto it = s.begin(); it != s.end(); it++)
    {
        if (isalnum(*it))
        {
            s.erase(s.begin(), it);
            break;
        }
    }
    //除去后缀符号
    for (auto it = s.end()-1; it != s.begin(); it--)
    {
        if (isalnum(*it))
        {
            s.erase(it+1, s.end());
            break;
        }
    }
    //转小写
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    //分割成word
    int startPos = 0;
    for (auto it = s.begin(); it != s.end();)
    {
        if (!isalnum(*it))
        {
            vs.push_back(s.substr(startPos, it-(s.begin()+startPos)));
            while (!isalnum(*it) && it!=s.end())
                it++;
            startPos = it-s.begin();
        }else
            it++;
    }
    vs.push_back(s.substr(startPos, s.length()-startPos));
    return vs;
}

int main()
{
    string s;
    bool flag = 0;
    map<string, int> res;
    int maxn = 0;
    vector<string> t;

    while (cin>>s)
    {
        t = deal(s);
        for (auto it = t.begin(); it != t.end(); it++)
        {
            res[*it]++;
            if (res[*it]>maxn)
                maxn = res[*it];
        }
    }
    for (auto it = res.begin(); it != res.end(); it++)
    {
        if (it->second == maxn)
        {
            printf("%s %d\n", it->first.c_str(), it->second);
            break;
        }
    }

    return 0;
}