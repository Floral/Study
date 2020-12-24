#include<stdio.h>
#include<string.h>

int main(){
    char a[100], b[100], c[100];

    scanf("%s",a);
    scanf("%s",b);
    scanf("%s",c);

    if (strcmp(a,b)>0)
        if (strcmp(a,c)>0)
            printf("%s", a);
        else
            printf("%s", c);
    else
        if (strcmp(b,c)>0)
            printf("%s", b);
        else
            printf("%s", c);
    
    return 0;
}