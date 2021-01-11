#include<cstdio>
#include<cstring>
#define maxn 21

struct bign
{
    int d[maxn];
    int len;
    bign(){
        memset(d, 0, sizeof(d));
        len = 0;
    }
};

bign str2Bign(char str[])
{
    bign ans;

    ans.len = strlen(str);
    for (int i = 0; i < ans.len; i++)
        ans.d[i] = str[ans.len-1-i] - '0';

    return ans;
}

bign multi(const bign &a, const int &b)
{
    bign ans;
    int temp = 0;
    int carry = 0;

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

    scanf("%s", str);
    bign a = str2Bign(str);

    bign b = multi(a, 2);

    if (a.len!=b.len)
    {
        printf("No\n");
        printBign(b);
    }else
    {
        int i = 0;
        int arr1[10] = {0};
        int arr2[10] = {0};
        for (i = 0; i < a.len; i++)
        {
            ++arr1[a.d[i]];
            ++arr2[b.d[i]];
        }
        
        for (i = 0; i < 10; i++)
        {
            if (arr1[i]!=arr2[i])
            {
                printf("No\n");
                printBign(b);
                break;
            }
        }
        if (i==10)
        {
            printf("Yes\n");
            printBign(b);
        }
    }
    
    return 0;
}