#include<stdio.h>
#include<string.h>
#define maxn 100
int left,chance;
char s[maxn],s2[maxn];
int win=0,lose=0;

int findChar(char *s,char c)
{
    int len = strlen(s);
    int sum = 0;
    for (size_t i = 0; i < len; ++i)
    {
        if (s[i]==c)
        {
            ++sum;
            s[i]=' ';
        }
    }
    return sum;
}

void guess(char c)
{
    int num=findChar(s,c);
    if (!num)
    {
        --chance;
    }
    else
    {
        left-=num;
    }
    
    if (!chance)
    {
        lose = 1;
    }
    else if(left == 0)
    {
        win = 1;
    }
    printf("%d %d\n",left,chance);
}

int main()
{
    int rnd=0;

    while (scanf("%d%s%s",&rnd,s,s2) == 3 && rnd != -1)
    {
        printf("Round %d\n",rnd);
        chance = 7;
        int length = strlen(s2);
        left = strlen(s);
        for (size_t i = 0; i < length; ++i)
        {
            guess(s2[i]);
            if (win || lose)
            {
                break;
            }
        }
        
        if (win)
            printf("You win.\n");
        else if(lose)
            printf("You lose.\n");
        else
            printf("You chickened out.\n");
        win=lose=0;
    }
    return 0;
}