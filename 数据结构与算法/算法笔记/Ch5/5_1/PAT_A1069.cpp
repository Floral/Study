#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 5

int str2int(char str[])
{
    //!BUG 这里有一个重要的问题，如果ans不初始化为0，那么会导致很严重的错误，具体与63行（t的赋值）有关
    int ans = 0, len = strlen(str);
    
    for (int i = 0; i < len; i++)
        ans = ans*10+(str[i]-'0');

    return ans;
}

void int2str(int x, char* p)
{
    // p[0] = x/1000+'0';
    // p[1] = x%1000/100+'0';
    // p[2] = x%100/10+'0';
    // p[3] = x%10+'0';
    // p[4] = '\0';
    //下面的写法更优雅一点，但是不一定效率更高2333
    for (int i = 0; i < maxn-1; i++)
    {
        p[i] = x%10+'0';
        x/=10;
    }
    p[maxn-1] = '\0';
    
    // return p;
}

bool incCmp(char a, char b)
{
    return a>b;
}

bool decCmp(char a, char b)
{
    return a<b;
}

int main()
{
    int t = 0;
    char temp[maxn] = {0};
    char inc[maxn] = {0};
    char dec[maxn] = {0};

    scanf("%d", &t);

    while (1)
    {
        int2str(t, temp);
        strcpy(inc, temp);
        strcpy(dec, temp);
        
        std::sort(inc, inc+4, incCmp);
        std::sort(dec, dec+4, decCmp);

        t = str2int(inc) - str2int(dec);
        printf("%s - %s = %04d\n",inc, dec, t);
        if (t==0 || t == 6174)
            break;
    }
    
    return 0;
}