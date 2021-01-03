#include<cstdio>
#include<cmath>
#include<cstring>
#define maxn 110

struct Float
{
    int num[maxn];  //保存原字符串去除小数点后的字符串，例如输入：123.45678，则num为12345678（下标从大到小）
    int len = 0;    //num的长度
    int dotPos = 0; //小数点理论上的下标，还是用上面那个例子，则dotPos为5（下标从0开始）
    Float(){
        memset(num, 0, sizeof(num));
    }
};
/*
Float addFloat(const Float &a, const Float &b)
{
    Float ans;
    int beginPos = 0;
    bool flag = a.dotPos>b.dotPos;

    if (flag)
    {
        ans.dotPos = a.dotPos;
        beginPos = a.dotPos - b.dotPos;
    }else
    {
        ans.dotPos = b.dotPos;
        beginPos = b.dotPos - a.dotPos;
    }
    
    int carry = 0, temp = 0;
    ans.len = beginPos;
    //! 这个for循环的判断条件有问题，因为下方的第二个加数的下标是i-beginPos，而不是i
    //! 假设flag为真，且beginPos==10，a.len=26, b.len==24, 那么我们加过的a、b的范围分别是[10, 26]、[0, 16]，显然，b的高位还有8位没有计算过
    //! 修复这个bug的方法我目前想到的就是加分支，两个for循环，不过这样的写法。。。。作为有一点代码洁癖的人来说，忍不了ε=( o｀ω′)ノ
    //! 如果有大佬知道有啥更好的写法欢迎讨论
    //todo 
    for (int i = beginPos; i<a.len || i<b.len; i++) 
    {
        if (flag){
            temp = a.num[i]+b.num[i-beginPos]+carry;
        }else{
            temp = b.num[i]+a.num[i-beginPos]+carry;
        }
        ans.num[ans.len++] = temp%10;
        carry = temp/10;
    }    

    if (carry!=0)
        ans.num[ans.len++] = carry;
    for (int i = 0; i < beginPos; i++)
    {
        if (flag)
            ans.num[i] = a.num[i];
        else
            ans.num[i] = b.num[i];
    }

    //消除末尾的0
    int cnt = 0;    //末尾0的个数
    while (ans.num[cnt]==0 && cnt < ans.len)
        ++cnt;
    if (cnt>0)
    {
        ans.len -= cnt;
        ans.dotPos -= cnt;
        for (int i = 0; i < ans.len; i++)
            ans.num[i] = ans.num[i+cnt];
    }
    
    return ans;
}
*/

Float addFloat(Float a, Float b)
{
    Float ans;
    int beginPos = 0;
    bool flag = a.dotPos>b.dotPos;

    //? 往小数更短的那个Float后面加0，使得小数点的位置对齐，从而可以直接应用大数加法的方法来算
    if (a.dotPos > b.dotPos)
    {
        int diff = a.dotPos-b.dotPos;
        for (int i = b.len; i >= 0; --i)
            b.num[i+diff] = b.num[i];
        for (int i = 0; i < diff; i++)
            b.num[i] = 0;
        b.len += diff;
        b.dotPos = a.dotPos;
    }else if (a.dotPos < b.dotPos)
    {
        int diff = b.dotPos-a.dotPos;
        for (int i = a.len; i >= 0; --i)
            a.num[i+diff] = a.num[i];   //! 这里我曾经右边的a.num[i]写成了b.num[i]，因为是直接从上面复制下来的，忘了改。。。浪费了很多时间/(ㄒoㄒ)/~~
        for (int i = 0; i < diff; i++)
            a.num[i] = 0;
        a.len += diff;
        a.dotPos = b.dotPos;
    }

    //important!
    ans.dotPos = a.dotPos;
    //? 下面是大数加法的标准流程
    int carry = 0, temp = 0;
    for (int i = 0; i<a.len || i<b.len; i++)
    {
        temp = a.num[i]+b.num[i]+carry;
        ans.num[ans.len++] = temp%10;
        carry = temp/10;
    }

    if (carry!=0)
        ans.num[ans.len++] = carry;

    //? 消除末尾的0
    int cnt = 0;    //末尾0的个数
    while (ans.num[cnt]==0 && cnt < ans.len)
        ++cnt;
    if (cnt>0)
    {
        ans.len -= cnt;
        ans.dotPos -= cnt;
        for (int i = 0; i < ans.len; i++)
            ans.num[i] = ans.num[i+cnt];
    }
    
    return ans;
}
// 这里有一个与我的思路类似的blog：https://blog.csdn.net/RPG_Zero/article/details/100187653

Float str2Float(char str[])
{
    Float ans;
    int len = strlen(str);

    for (int i = 0; i < len; ++i)
    {
        if (str[len-1-i] == '.')
            ans.dotPos = i;
        else
            ans.num[ans.len++] = str[len-1-i]-'0';
    }
    return ans;
}

void printFloat(const Float &a)
{
    int len = a.len+1;
    
    char str[len+1];
    int cnt = 0;    //? cnt是a中num的计数器，因为要插入小数点，所以不能直接用i
    for (int i = 0; i < len; ++i)
    {
        if (a.len-i == a.dotPos)
            str[i] = '.';
        else
        {
            str[i] = a.num[a.len-1-cnt]+'0';
            ++cnt;
        }
    }
    str[len] = '\0';
    printf("%s\n", str);
}

int main()
{
    int N;

    while(scanf("%d", &N)!=EOF)
    {
        while (N--)
        {
            char str1[maxn], str2[maxn];
            scanf("%s %s", str1, str2);

            Float a = str2Float(str1);
            Float b = str2Float(str2);

            Float sum = addFloat(a, b);
            printFloat(sum);
        }
    }
    
    return 0;
}