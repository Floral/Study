#include<stdio.h>
#include<string.h>
#include<ctype.h>
#define LOCAL

const char* rev = "A   3  HIL JM O   2TUVWXY51SE Z  8 ";
const char* msg[] = {"not a palindrome","a regular palindrome"
                    ,"a mirrored string","a mirrored palindrome"};

char mirror(char c)
{
    if (isalpha(c)) {
        return rev[c-'A'];
    }
    else
    {
        return rev[c-'0'+25];
    }
}

int main()
{
    char s[30];
#ifdef LOCAL
    freopen("data.in","r",stdin);
#endif
    while(~scanf("%s",s)){
        /* code */
        int m=1,n=1;
        int len = strlen(s);
        for(size_t i = 0; i < (len+1)/2; i++)//这里判断循环停止未位置有坑——或许是我太傻2333
        {
            if (s[len-1-i]!=mirror(s[i])) {
                m=0;
            }
            if (s[i]!=s[len-1-i]) {
                n=0;
            }
        }
        printf("%s -- is %s.\n\n",s,msg[m*2+n]);
    }
    return 0;
}