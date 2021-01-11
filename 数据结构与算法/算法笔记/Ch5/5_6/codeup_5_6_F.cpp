#include<cstdio>
#include<cstring>
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

bign str2bign(char str[]){
    bign ans;

    int len = strlen(str);
    for (int i = 0; i < len; i++)
        ans.d[i] = str[len-1-i] - '0';
    ans.len = len;

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

bign divide(bign a, int m, int b, int& r) {//r是引用变量，所以返回实参，作用域大，每次可返回值
	bign c;
	c.len = a.len;
	r = 0;
	for (int i = a.len - 1;i >= 0;i--) {
		r = r * m + a.d[i];	
        //! 因为是m进制的，所以乘上m（这个数学原理对这题很有用，大大减少工作量）
        //! 这个方法的原理是取余的运算规则：https://blog.csdn.net/ash_zheng/article/details/38541777
        //! 我一开始想的是先把输入的M进制数转为10进制，再转为目标进制，这样很繁琐
		if (r < b)
            c.d[i] = 0;
		else {	//相当于除b取余吧
			c.d[i] = r / b;
			r %= b;
		}
	}
	while (c.len - 1 >= 1 && c.d[c.len - 1] == 0)
		c.len--;	//消除高位的0
	return c;
}

void printBign(const bign &a)
{
    char str[maxn];
    for (int i = 0; i < a.len; ++i)
    {
        str[i] = a.d[a.len-1-i]+'0';
    }
    str[a.len] = '\0';
    printf("%s\n",str);
}

int main()
{
    char str[maxn];

    while (scanf("%s", str)!=EOF)
    {
        bign a = str2bign(str);

        char bin[maxn*4], ans[maxn*2];
        int len = 0;
        int r = 0;
        do
        {
            a = divide(a, 10, 2, r);    //10转2
            bin[len++] = r+'0';
        } while (!(a.len==1 && a.d[0]==0));
        
        bin[len] = '\0';
        
        len = 0;
        a = str2bign(bin);
        do
        {
            a = divide(a, 2, 10, r);    //2转10
            ans[len++] = r+'0';
        } while (!(a.len==1 && a.d[0]==0));
        ans[len] = '\0';
        for (int i = len-1; i >= 0; --i)
            printf("%c", ans[i]);
        putchar('\n');        

        //* 这是我的方法，思路很“普通”
        // bign ans;
        // int r = 0;
        // int t = 0;
        // do
        // {
        //     a = divide(a, 10, 2, r);
        //     ans = add(multi(ans, 2), r);
        // } while (!(a.len==1 && a.d[0]==0));
        
        // printBign(ans);
    }

    return 0;
}