#include<stdio.h>
#include<string.h>
#define maxn 10000000+10

    char s[maxn];
int main()
{
    scanf("%s",s);
    int tot=0;
    for(size_t i = 0; i < strlen(s); i++)
    {
        /* code */
        if (s[i]=='1') {
            /* code */
            tot++;
        }
        
    }
    printf("%d\n",tot);
    return 0;
}