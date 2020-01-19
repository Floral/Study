#include<stdio.h>
#include<string.h>
#include<ctype.h>
#define MAX 10010
char s[MAX];

int main()
{
    // freopen("data.in","r",stdin);

    int T;
    scanf("%d",&T);
    
    while(T--){
        scanf("%s",s);
        int len = strlen(s);

        double sum = 0;
        for(size_t i = 0; i < len; i++)
        {
            double t;
            int n;
            switch (s[i])
            {
                case 'C':
                    t=12.01;
                    break;
                case 'H':
                    t=1.008;
                    break;
                case 'O':
                    t=16.00;
                    break;
                case 'N':
                    t=14.01;
                    break;
                default:
                    break;
            }
            n=0;

            while(isdigit(s[i+1])){
                n=n*10+s[i+1]-48;
                i++;
            }
            if (n==0) {
                n++;
            }
            sum+=(n*t);
        }
            printf("%.3lf\n",sum);
    }
    
    return 0;
}