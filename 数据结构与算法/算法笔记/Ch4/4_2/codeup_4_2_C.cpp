#include<cstdio>
#include<cstring>
#define maxn 100005

int hashTable[maxn] = {0};
int arr[maxn] = {0};

int main()
{
    int N;

    while (scanf("%d", &N)!=EOF)
    {
        /* code */
        memset(hashTable, 0 ,sizeof(hashTable));
        memset(arr, 0 ,sizeof(arr));

        for (size_t i = 0; i < N; i++)
        {
            scanf("%d", arr+i);
            hashTable[arr[i]]++;
        }

        for (size_t i = 0; i < N; i++)
        {
            if (hashTable[arr[i]] == 1)
            {
                printf("%d\n", arr[i]);
                break;
            }else if (i==N-1)
            {
                printf("None\n");
            }
        }
    }
    
    return 0;
}