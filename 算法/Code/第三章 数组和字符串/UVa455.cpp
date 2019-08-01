#include<stdio.h>
#include<string.h>
#define MAX 100

char s[MAX];
int main()
{
    freopen("data.in","r",stdin);
    int T;
    scanf("%d",&T);
    
    while (T--)
    {
        scanf("%s",s);
        int len = strlen(s);

        for (size_t i = 1; i <= len; i++)
        {
            
            if (len%i==0)   //判断字符串长度是否是i的整数倍
            {
                int flag = 1;
                for (size_t j = 0; j < len/i ; j++)
                {
                    for (size_t k = 1; j+i*k < len; j++)
                    {
                        if (s[j]!=s[j+i*k])
                        {
                            flag = 0;
                            break;
                        }
                    }
                    if (flag == 0)
                    {
                        break;
                    }
                    
                }
                if (flag)
                {
                    printf("%d\n",i);
                    break;
                }
                
            }
        }
        if (T)
        {
            printf("\n");
        }
    }
    
    return 0;
}