#include<cstdio>
#include<cstring>

int hashTable[11] = {0};

int main()
{
    int t;
    while (scanf("%d", &t)!=EOF)
    {
        int max = 0;
        memset(hashTable, 0, sizeof(hashTable));
        hashTable[t]++;
        for (int i = 0; i < 19; i++)
        {
            scanf("%d", &t);
            hashTable[t]++;
            if (hashTable[t]>max)
                max = hashTable[t];
        }
        
        for (int i = 1; i <= 10; i++)
        {
            if (hashTable[i]==max)
            {
                printf("%d\n", i);
                break;
            }
        }
    }

    return 0;
}