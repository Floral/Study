#include<cstdio>
#include<iostream>
#include<string>

using namespace std;

/*
double str2double(string s, int N)
{
    double ans = .0;

    int dotPos = -1, exp = 0;
    int len = s.length();

    for (int i = 0; i < len; i++)
    {
        if (s[i]!='.')
            ans = ans*10+s[i]-'0';
        else
            dotPos = i;        
    }

    if (dotPos != -1)
        exp = (len-1-dotPos);

    while (exp--)
        ans *= 0.1;

    return ans;
}
*/

string deal(string s, int N, int &exp)
{
    string ans;

    int i = 0;
    exp = 0;
    //* 除去前置无意义的0
    while (s[i]=='0')
        ++i;
    s.erase(0, i);

    if (s.length()==0)
    {
        ans = '0';
    }else if (s[0] == '.')
    {
        s.erase(s.begin()); //删除小数点
        i = 0;
        while (s[i]=='0' && i<s.length()-1) //统计exp
        {
            ++i;
            --exp;
        }
        s.erase(0, i);
        if (s=="0") //如果s为"0",那么exp直接为0,否则会因为上面的统计而不是0,导致结果错误
            exp = 0;
    }else
    {
        i = 0;
        while (s[i]!='.' && i<s.length())
        {
            ++i;
            ++exp;
        }
        if (i!=s.length())
            s.erase(exp, 1);
    }
    for (i = 0; i<N && i<s.length(); i++)
        ans += s[i];
    //* 位数不够则补0
    for (i = ans.length(); i < N; i++)
        ans += '0';
    return ans;
}

int main()
{
    int N;
    string s1, s2;

    cin>>N>>s1>>s2;

    int exp1 = 0, exp2 = 0;
    string a = deal(s1, N, exp1);
    string b = deal(s2, N, exp2);

    if (a==b && exp1==exp2)
    {
        printf("YES 0.%s*10^%d\n", a.c_str(), exp1);
    }else
    {
        printf("NO 0.%s*10^%d 0.%s*10^%d\n", a.c_str(), exp1, b.c_str(), exp2);
    }
    
    

    /*
    int dotPos1, dotPos2;
    dotPos1 = s1.find('.');
    dotPos2 = s2.find('.');
    if (dotPos1 == string::npos)
        dotPos1 = s1.length();
    if (dotPos2 == string::npos)
        dotPos2 = s2.length();
    
    // printf("%lf\n", str2double(s1));

    int i1 = 0, i2 = 0, limit1, limit2;
    while ((s1[i1]=='0' || s1[i1]=='.'))
        ++i1;
    while ((s2[i2]=='0' || s2[i2]=='.'))
        ++i2;

    limit1 = i1+N;
    limit2 = i2+N;
    for (; i1 < limit1 && i2 < limit2; i1++, i2++)
    {
        if (s1[i1]!=s2[i2])
            break;
    }
    int exp1 = (limit1-N < dotPos1) ? dotPos1 : -(limit1-N-1-dotPos1);
    int exp2 = (limit2-N < dotPos2) ? dotPos2 : -(limit2-N-1-dotPos2);

    if (i1!=limit1)
    {
        if (limit1-N == s1.length())
            limit1 -= 1;
        if (limit2-N == s2.length())
            limit2 -= 1;
        
        printf("NO 0.%s*10^%d 0.%s*10^%d\n", s1.substr(limit1-N, N).c_str(), exp1, s2.substr(limit2-N, N).c_str(), exp2);
    }
    else
    {
        printf("YES 0.%s*10^%d\n", s1.substr(limit1-N, N).c_str(), exp1);
    }
    */
    
    return 0;
}