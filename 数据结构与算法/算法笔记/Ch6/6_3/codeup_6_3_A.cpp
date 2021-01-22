#include<iostream>
#include<string>
#include<cmath>

using namespace std;

double str2double(string str)
{
    double ans = .0;
    //* flag1是底数负号标志, flag2是指数负号标志
    int i = 0, end = 0, dotPos = str.length(), flag1 = 0, flag2 = 0;
    int exp = 0;
    if (str[i]=='-')
    {
        flag1 = 1;
        ++i;
    }
    //* end是e前部分的末尾
    if (str.find('e')!=string::npos)
        end = str.find('e');
    else if (str.find('E')!=string::npos)
        end = str.find('E');
    else
        end = str.length();
    
    //* 处理指数部分
    for (int t = end+1; t < str.length(); t++)
    {
        if (str[t]=='-')
            flag2 = 1;
        else
            exp = exp*10+str[t]-'0';
    }
    if (flag2)
        exp = -exp;

    //* 处理底数部分
    for (; i < end; i++)
    {
        if (str[i]!='.')
            ans = ans*10+str[i]-'0';
        else
            dotPos = i;
    }
    //* 判断是否存在小数点
    if (dotPos!=str.length())
        exp = exp-(end-1-dotPos);
    
    if (flag1)
        ans = -ans;
    
    ans = ans*pow(10, exp);

    return ans;
}

string double2str(double a)
{
    string ans;

    int flag = a<0;
    int exp = 0;
    double temp = abs(a);
    //* 大于10的话,exp应该是正
    while ((int)temp>=10)
    {
        ++exp;
        temp /= 10;
    }
    //* 小于1的话,exp应该是负
    while (temp<1)
    {
        --exp;
        temp *= 10;
    }

    char str[12];
    sprintf(str, "%.9lf", temp);

    if (flag)
        ans+='-';
    ans+=string(str);
    //* 除去末尾的0
    auto it = ans.end()-1;
    while (*(it)=='0')
        --it;
    ans.erase(it+1, ans.end());

    sprintf(str, "e%d", exp);
    ans += string(str);

    return ans;
}

//! 不知道为何超时......
int main()
{
    string str1, str2;

    while (cin>>str1>>str2)
    {
        double a = str2double(str1);
        double b = str2double(str2);

        string s = double2str(a);
        cout<<s<<endl;
    }

    return 0;
}