#include<cstdio>
#include<algorithm>
#define maxn 100010

using namespace std;

struct Node
{
    int addr;
    int data;
    int next;
    bool flag = false;
}node[maxn];

bool cmp(Node &a, Node &b)
{
    if (a.flag == false || b.flag == false)
        return a.flag > b.flag;
    else
        return a.data < b.data;
}

//! 目前这个解法还是有问题
int main()
{
    int N, head;

    scanf("%d %d", &N, &head);

    int addr, data, next;
    for (int i = 0; i < N; i++)
    {
        scanf("%d %d %d", &addr, &data, &next);
        node[addr].addr = addr;
        node[addr].data = data;
        node[addr].next = next;
    }

    int p = head, count = 0;
    while (p!=-1)
    {
        node[p].flag = true;
        count++;
        p = node[p].next;
    }    

    sort(node, node+maxn, cmp);
    head = node[0].addr;
    if (count == 0)
    {
        printf("0 -1\n");
    }else
    {
        printf("%d %05d\n", count, head);
        for (int i = 0; i < count-1; i++)
        {
            printf("%05d %d %05d\n", node[i].addr, node[i].data, node[i+1].addr);
        }
        printf("%05d %d -1\n", node[count-1].addr, node[count-1].data);
    }
    return 0;
}