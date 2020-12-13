#include<cstdio>
#include<cmath>
#define num 8

int res[100][num+1] = {0};
int seq[num+1] = {0};
bool hashTable[num+1] = {false};
int count = 0;

void generateSeq(int index)
{
    if (index == num+1)
    {
        count++;
        // if (count == rank)
        // {
            for (size_t i = 1; i < num+1; i++)
            {
                // printf("%d", seq[i]);
                res[count][i] = seq[i];
            }
            // putchar('\n');
        // }
        return;
    }
    
    for (int i = 1; i < num+1; i++)  //尝试把第index行的皇后放在第i列
    {
        if (hashTable[i] == false)
        {
            int flag = 1;   //必须要有这个flag
            for (int pre = 1; pre < index; pre++)    //第pre行的皇后
            {
                if (abs(i - seq[pre]) == abs(index-pre))
                {
                    flag = 0;
                    break;      
                    //如果没有flag,这里就要用return以避免后续代码被执行
                    //但是用return也不符合题意,因为return后就不会继续尝试当前i之后的列了
                }
            }
            
            if (flag)
            {
                seq[index] = i;
                hashTable[i] = true;
                generateSeq(index+1);
                hashTable[i] = false;
            }
        }
    }
}

int main()
{
    int n, rank;
    scanf("%d", &n);
    generateSeq(1);
    printf("%d\n", count);
    while (n--)
    {
        // count = 0;
        scanf("%d", &rank);
        // generateSeq(1, rank);
        for (size_t i = 1; i < num+1; i++)
        {
            printf("%d", res[rank][i]);
        }
        printf("\n");
    }
    
    return 0;
}