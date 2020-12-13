#include<cstdio>
#include<cstring>
#define maxL 10010

char str1[maxL] = {0};
char str2[maxL] = {0};
char res[maxL] = {0};
bool hashTable[128] = {false};

int main()
{
    while (gets(str1))
    {
        memset(hashTable, 0, sizeof(hashTable));

        gets(str2);
        for (size_t i = 0; i < strlen(str2); i++)
        {
            hashTable[str2[i]] = true;
        }

        int j = 0;
        for (size_t i = 0; i < strlen(str1); i++)
        {
            if (hashTable[str1[i]]!=true)
                // printf("%c", str1[i]);
                res[j++] = str1[i];
        }
        res[j] = '\0';
        printf("%s\n", res);
    }

    return 0;
}