#include<cstdio>
#include<cmath>

int main()
{
    int N, i;
    char C;

    scanf("%d %c", &N, &C);
    if (N<3 || N>20)
    {
        return 0;
    }

    int columns = N, rows = (int)round(N/2.0);
    //�������������е�С������ˡ���������ֱ�������ϵ��ж���ż���ķ���
    for (i = 0; i < columns; ++i)
    {
        printf("%c", C);
    }
    printf("\n");

    rows-=2;
    while (rows--)
    {
        for (i = 0; i < columns; ++i)
        {
            if (i==0 || i==columns-1)
            {
                printf("%c", C);
            }else
            {
                printf(" ");
            }
        }
        printf("\n");
    }

    for (i = 0; i < columns; ++i)
    {
        printf("%c", C);
    }

    return 0;
}
