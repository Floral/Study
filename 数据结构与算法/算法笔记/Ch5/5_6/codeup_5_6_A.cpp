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

bign str2bign(char str[]){
    bign ans;

    int len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        ans.d[i] = str[len-1-i] - '0';
    }
    ans.len = len;

    return ans;
}

bign addBign(const bign &a,const bign &b){
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

void printBign(const bign &a){
    char str[a.len+1];
    for (int i = 0; i < a.len; i++)
    {
        str[i] = a.d[a.len-1-i]+'0';
    }
    str[a.len] = '\0';
    printf("%s\n",str);
}

int main(){

    char str1[maxn], str2[maxn];

    while (scanf("%s %s", str1, str2)!=EOF){
        bign a = str2bign(str1);
        bign b = str2bign(str2);
        bign c = addBign(a, b);

        printBign(c);        
    }
    
    return 0;
}