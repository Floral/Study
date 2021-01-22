#include<cstdio>
#include<algorithm>
#include<string.h>

using namespace std;

int main()
{
    char str[10];

    while (scanf("%s", str)!=EOF)
    {
        int len = strlen(str);
        do
        {
            printf("%s\n", str);
        } while (next_permutation(str, str+len));
        putchar('\n');
    }
    
    return 0;
}