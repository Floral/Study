#include<cstdio>
#include<cstring>
#include<cmath>
#define maxn 10001

struct bign{
    int d[maxn];
    int len;

    bign(){
        memset(d, 0, sizeof(d));
        len = 0;
    }
};

bign str2bign(char str[]){
    bign temp;

    int len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        //!!! 这个if条件写错了，应该是str[len-1-i]，而不是str[i]
        if (str[i] >= '0' && str[i] <= '9')
            temp.d[i] = str[len-1-i] - '0';
        else
            temp.d[i] = str[len-1-i] - 'A' + 10;
    }
    temp.len = len;

    return temp;
}

//* a是10进制的bign
//* b是除数
//* r是余数
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
		else {	//相当于除k取余吧
			c.d[i] = r / b;
			r %= b;
		}
	}
	while (c.len - 1 >= 1 && c.d[c.len - 1] == 0)
		c.len--;	//消除高位的0
	return c;
}

// 参考自：
// https://blog.csdn.net/weixin_44774255/article/details/108512018

int main()
{
    int M, N;
    char str[maxn];

    while (scanf("%d%d", &M, &N)!=EOF)
    {
        scanf("%s", str);
        bign a = str2bign(str);
        char ans[maxn];
        int r = 0, i = 0, j;
		do {
			a = divide(a, M, N, r);//利用每次返回的余数来得到n进制的值，a并没有作用，只是来接受一个bign型的数据而已，关键在于r的得到
			if (r >= 0 && r <= 9) 
                ans[i++] = r + '0';
			else 
                ans[i++] = r - 10 + 'a';
		} while (!(a.d[0] == 0 && a.len == 1));	//当为0时退出循环
		ans[i] = '\0';
		for (j = i - 1;j >= 0;j--)
			printf("%c", ans[j]);
        putchar('\n');
    }
    
    return 0;
}