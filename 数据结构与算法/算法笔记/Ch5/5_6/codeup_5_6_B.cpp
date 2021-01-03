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
};

bign multi(const bign &a, const int &b)
{
    bign ans;
    int temp = 0;
    int carry = 0;

    for (int i = 0; i < a.len; i++)
    {
        temp = a.d[i]*b+carry;  //!总是容易忘了加carry！
        ans.d[ans.len++] = temp%10;
        carry = temp/10;
    }

    while (carry!=0)
    {
        ans.d[ans.len++] = carry%10;
        carry/=10;
    }
    
    return ans;
}

bign factorial(int N)
{
    bign ans;
    ans.d[ans.len++] = 1;

    for (int i = 1; i <= N; i++)
    {
        ans = multi(ans, i);
    }    

    return ans;
}

void printBign(const bign &a){
    char str[a.len+1];
    for (int i = 0; i < a.len; i++)
    {
        str[i] = a.d[a.len-1-i]+'0';
    }
    str[a.len] = '\0';
    printf("%s\n",str);
}

int main()
{
    int N;

    while (scanf("%d", &N)!=EOF)
    {
        bign ans = factorial(N);

        printBign(ans);
    }
    
    return 0;
}