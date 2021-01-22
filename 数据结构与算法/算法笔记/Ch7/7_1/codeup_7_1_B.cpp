#include<cstdio>
#include<iostream>
#include<stack>
#include<string>
using namespace std;

int main()
{
    int N;

    while (scanf("%d", &N)!=EOF)
    {
        string s;
        stack<char> st;
        while (N--)
        {
            cin >> s;
            int len = s.length();
            bool flag = true;   //默认符号匹配
            for (int i = 0; i < len; i++)
            {
                if (s[i]=='[' || s[i]=='{' || s[i]=='(')
                    st.push(s[i]);
                else if (s[i]==']' || s[i]=='}' || s[i]==')')
                {
                    if (st.empty()) //如果栈为空,说明右括号多了,直接就能判断有问题
                    {
                        flag = false;
                        break;
                    }
                    char t = st.top();
                    switch (s[i])
                    {
                    case ']':
                        if (t!='[')
                            flag = false;
                        break;
                    case '}':
                        if (t!='{')
                            flag = false;
                        break;
                    case ')':
                        if (t!='(')
                            flag = false;
                        break;
                    }
                    if (!flag)
                        break;
                    st.pop();
                }
            }
            if (!st.empty())    //如果栈不为空,说明左括号多了 
            {
                flag = false;
                while (!st.empty())
                    st.pop();
            }
            
            if (flag)
                printf("yes\n");
            else
                printf("no\n");
        }
    }

    return 0;
}