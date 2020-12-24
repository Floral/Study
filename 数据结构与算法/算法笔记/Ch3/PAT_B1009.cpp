#include<cstdio>

char strs[80][80];

int main(){
    int i = 0;
    while (scanf("%s", strs[i])!=EOF)
    {
        ++i;
    }
    for (i = i-1; i>=0; i--)
    {
        printf("%s", strs[i]);
        if (i>0)
        {
            printf(" ");
        }
    }
    return 0;
}