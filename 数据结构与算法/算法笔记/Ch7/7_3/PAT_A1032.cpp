#include<cstdio>
#define maxn 100000

struct Node
{
    char data;
    int nextAddr;    
}node[maxn];

bool hash[maxn] = {false};  //node存在于word1中的flag，也可以整合进node结构体中

int main()
{
    int word1, word2;
    int N;

    scanf("%d %d %d", &word1, &word2, &N);

    int addr, next;
    char data;
    while (N--)
    {
        scanf("%d %c %d", &addr, &data, &next);

        node[addr].data = data;
        node[addr].nextAddr = next;
    }
    
    //遍历word1的节点
    while (word1!=-1)
    {
        hash[word1] = true;
        word1 = node[word1].nextAddr;
    }

    while (word2!=-1)
    {
        if (hash[word2])
            break;
        else
            word2 = node[word2].nextAddr;
    }
    if (word2!=-1)
        printf("%05d", word2);
    else
        printf("-1");

    return 0;
}