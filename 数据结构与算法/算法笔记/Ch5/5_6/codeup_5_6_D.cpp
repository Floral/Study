#include<cstdio>
#include<cstring>
#include<cmath>
#define maxn 1001

struct bign{
    int d[maxn];
    int len;

    bign(){
        memset(d, 0, sizeof(d));
        len = 0;
    }
    bign(int n){
        memset(d, 0, sizeof(d));
        len = 0;
        //! 如果把上面两句换成bign();的话会有bug。。。调试就能看到哪里有bug了，不知道为啥会出现这个bug。。。太菜了
        while (n!=0)
        {
            d[len++] = n%10;
            n/=10;
        }
    }
};

char radixMap[36+1] = {0};
bign str2bign(char str[], int radix);
bign add(const bign &a, const bign &b);
bign multi(const bign &a, const int &b);
bign divide(const bign &a, int b, int &r);

void init()
{
    for (int i = 0; i < 10; i++)
        radixMap[i] = i+'0';
    for (int i = 10; i < 37; i++)
        radixMap[i] = 'a'+i-10;
}

bign str2bign(char str[], int radix){
    bign temp;

    int len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        //!!! 这个if条件写错了，应该是str[len-1-i]，而不是str[i]
        // if (str[i] >= '0' && str[i] <= '9')
        if (str[len-1-i] >= '0' && str[len-1-i] <= '9')
            temp.d[i] = str[len-1-i] - '0';
        else
            temp.d[i] = str[len-1-i] - 'A' + 10;
    }
    temp.len = len;

    bign ans;
    bign t;

    for (int i = len-1; i >= 0; --i)
    {
        t = multi(ans, radix);
        ans = add(t, temp.d[i]);
    }

    return ans;
}

bign add(const bign &a, const bign &b)
{
    bign ans;
    int carry = 0;
    int temp = 0;    
    for (int i = 0; i<a.len || i<b.len; i++)
    {
        temp = a.d[i]+b.d[i]+carry;
        ans.d[ans.len++] = temp%10;
        carry = temp/10;
    }

    if (carry!=0)
        ans.d[ans.len++] = carry;

    return ans;
}

bign multi(const bign &a, const int &b)
{
    bign ans;
    int carry = 0;
    int temp = 0;

    for (int i = 0; i < a.len; i++)
    {
        temp = a.d[i]*b + carry;
        ans.d[ans.len++] = temp%10;
        carry = temp/10;
    }

    while (carry!=0)
    {
        ans.d[ans.len++] = carry%10;
        carry /= 10;
    }
    
    return ans;
}

//* a是10进制的bign
//* b是除数
//* r是余数
bign divide(const bign &a, int b, int &r)  
{
    bign ans;
    ans.len = a.len;

    for (int i = a.len-1; i >= 0; i--)
    {
        r = r*10+a.d[i];
        if (r<b)
            ans.d[i] = 0;
        else
        {
            ans.d[i] = r/b;
            r = r%b;
        }
    }
    while (ans.len-1>=1 && ans.d[ans.len-1]==0)
        ans.len--;
    return ans;
}

//* 我这样的方法也行，只不过太麻烦了
int main()
{
    int M, N;
    char str[maxn];

    init();
    while (scanf("%d%d", &M, &N)!=EOF)
    {
        scanf("%s", str);
        bign a = str2bign(str, M);
        int r = 0;
        char result[maxn];
        int len;
        for (len = 0; !(a.len==1 && a.d[0]==0); len++)
        {
            r = 0;
            a = divide(a, N, r);
            result[len] = r;
        }
        result[len] = '\0';
        
        for (int i = len-1; i >= 0; --i)
        {
            printf("%c", radixMap[result[i]]);
        }
        putchar('\n');
    }
    
    return 0;
}