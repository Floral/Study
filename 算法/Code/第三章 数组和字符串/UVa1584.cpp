#include<stdio.h>
#include<string.h>
#define LOCAL
#define MAX 110

char s[MAX];

int main()
{
    int i,n,len;
#ifdef LOCAL
    freopen("data.in","r",stdin);
#endif
    scanf("%d",&n);
    while(n--)
    {
        int ans=0;
        scanf("%s",s);
        len=strlen(s);

        for(i = 1; i < len; i++)
        {
            for(size_t j = 0; j < len; j++)
            {
                if (s[(ans+j)%len]>s[(i+j)%len]) {
                    ans=i;
                    break;
                }else if(s[(ans+j)%len]<s[(i+j)%len])
                {
                    break;
                }
            }
        }
    
        for( i = 0; i < len; i++)
        {
            printf("%c",s[(ans+i)%len]);
        }
    printf("\n");
    }
    return 0;
}