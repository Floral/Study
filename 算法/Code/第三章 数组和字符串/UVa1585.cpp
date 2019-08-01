#include<stdio.h>
#include<string.h>
#define MAX 90

int main()
{
    // freopen("data.in","r",stdin);
    char s[MAX],len;
    int n;
    scanf("%d",&n);
    while(n--){
        int t=0,score=0;
        scanf("%s",s);
        len=strlen(s);

        for(size_t i = 0; i < len; i++)
        {
            if (s[i]=='O') {
                score+=(++t);
            }else 
            {
                t=0;
            }
        }
        printf("%d\n",score);
    }
    
    return 0;
}