#include<stdio.h>
#include<string.h>
char s[] = "`1234567890-=QWERTYUIOP[]\\ASDFGHJKL;'ZXCVBNM,./";
int main()
{
    char c;

    while((c=getchar())!=EOF){
        /* code */
        int i;
        for( i = 1; i < strlen(s); i++)
        {
            /* code */
            if (c==s[i]) {
                /* code */
                printf("%c",s[i-1]);
                break;
            }
        }
        if (i==strlen(s)) {
            /* code */
            printf("%c",c);
        }
        
    }
    
    return 0;
}