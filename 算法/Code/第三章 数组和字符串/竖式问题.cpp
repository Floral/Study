#include<stdio.h>
#include<string.h>

int main()
{
    char s[20],buf[99];
    int count=0;

    scanf("%s",s);

    for(size_t abc = 111; abc <= 999; abc++)
    {
        for(size_t de = 11; de <= 99; de++)
        {
            int x=abc*(de%10),y=abc*(de/10),z=abc*de;
            sprintf(buf,"%d%d%d%d%d",abc,de,x,y,z);
            // printf("%d %d %d %d %d\n",abc,de,x,y,z);
            int check = 1;
            for(size_t i = 0; i < strlen(buf); i++)
            {
                
                if (strchr(s,buf[i])==NULL) {
                    check=0;
                }
                
            }
            
            if (check) {
                printf("<%d>\n%5d\nX%4d\n-----\n%5d\n%4d \n-----\n%5d\n\n",
                        ++count,abc,de,x,y,z);
            }
            
        }
        
    }
    printf("The number of solutions = %d\n",count);
    return 0;
}