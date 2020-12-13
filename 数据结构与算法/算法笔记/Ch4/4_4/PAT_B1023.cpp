#include<cstdio>

int numTable[10] = {0};

int main()
{
    for (size_t i = 0; i < 10; i++)
    {
        scanf("%d", numTable+i);
    }

    for (size_t i = 1; i < 10; i++)
    {
        if (numTable[i]!=0)
        {
            printf("%d", i);
            numTable[i]--;
            break;
        }
    }
    for (size_t i = 0; i < 10; i++)
    {
        for (size_t j = 0; j < numTable[i]; j++)
        {
            printf("%d", i);
        }
    }
    
    return 0;
}