#include<cstdio>
#include<string.h>

const int N = 100010;

int main()
{
    int n;
    scanf("%d",&n);
    int num, grades[N], max = 1;
    memset(grades, 0, sizeof(grades));   
    while (n--)
    {
        int tmp = 0;
        scanf("%d %d", &num, &tmp);
        grades[num] += tmp;
        if (grades[num] > grades[max])
        {
            max = num;
        }
    }
    printf("%d %d", max, grades[max]);
    return 0;
}