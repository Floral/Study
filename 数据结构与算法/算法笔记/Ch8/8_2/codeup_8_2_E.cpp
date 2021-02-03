#include<cstdio>
#include<cstring>
#include<queue>

using namespace std;
bool vis[105][105][105];    //是否入栈
// int dis[101][100][100];     //步数
int C[3];    //a b c的容量

struct Node
{
    int sta[3]; //a b c的剩余状态
    int step = 0;       //步数
    Node(){}
    Node(int a, int b, int c):sta{a, b, c} {}
};

void Push(queue<Node> &q, const Node &now, int source, int target)   //倒油，从source倒到target
{
    Node next = now;
    if (next.sta[source] == 0)
        return;
    else if (next.sta[source] >= C[target]-next.sta[target])
    {
        next.sta[source]-=(C[target]-next.sta[target]);
        next.sta[target]=C[target];
    }else
    {
        next.sta[target]+=next.sta[source];
        next.sta[source]=0;
    }
    if (!vis[next.sta[0]][next.sta[1]][next.sta[2]])
    {
        vis[next.sta[0]][next.sta[1]][next.sta[2]] = true;
        next.step = now.step+1;
        q.push(next);
    }
}

bool check(const int sta[3], const int &k)
{
    for (int i = 0; i < 3; i++)
    {
        if (sta[i]==k)
            return true;
    }
    return false;
}

int bfs(int a, int b, int c, int k)
{
    queue<Node> q;
    Node now;

    q.push(Node(a, b, c));
    vis[a][b][c] = true;
    while (!q.empty())
    {
        now = q.front();
        q.pop();

        if (check(now.sta, k))
            return now.step;

        Push(q, now, 0, 1);
        Push(q, now, 0, 2);
        Push(q, now, 1, 0);
        Push(q, now, 1, 2);
        Push(q, now, 2, 0);
        Push(q, now, 2, 1);
    }
    return -1;
}

int main()
{
    int k;
    while(scanf("%d %d %d %d", &C[0], &C[1], &C[2], &k)!=EOF)
    {
        memset(vis, 0, sizeof(vis));
        int ans = bfs(C[0], 0, 0, k);
        if (ans!=-1)
            printf("yes\n%d\n", ans);
        else
            printf("no\n");
    }
    return 0;
}