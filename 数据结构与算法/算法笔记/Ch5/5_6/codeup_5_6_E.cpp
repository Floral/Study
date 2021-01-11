#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 1001

struct bign{
    int d[maxn];
    int len;

    bign(){
        memset(d, 0, sizeof(d));
        len = 0;
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

bign arr[101];

bool cmp(const bign &a, const bign &b)
{
    bool ans;

    if (a.len < b.len)
        ans = true;
    else if (a.len > b.len)
        ans = false;
    else
    {
        for (int i = a.len-1; i >= 0; --i)
        {
            if (a.d[i]<b.d[i])
            {
                ans = true;
                break;
            }else if (a.d[i]>b.d[i])
            {
                ans = false;
                break;   
            }
        }
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
    int N;

    while (scanf("%d", &N)!=EOF)
    {
        char str[maxn];
        for (int i = 0; i < N; i++)
        {
            scanf("%s", str);
            arr[i] = str2bign(str);
        }

        std::sort(arr, arr+N, cmp);

        for (int i = 0; i < N; i++)
        {
            printBign(arr[i]);
        }
    }
    
    return 0;
}