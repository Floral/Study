#include<cstdio>
#include<queue>
using namespace std;
const int maxn=101;

struct Node
{
    int x, y;
    int dis = 0;
};
char maze[maxn][maxn];
bool inQueue[maxn][maxn] = {false};
int M, N;
int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};
Node s, t;

bool judge(const Node &a)
{
    if (a.x<0 || a.x>=M || a.y<0 || a.y>=N)
        return false;
    else if (maze[a.x][a.y]=='*')
        return false;
    else if (inQueue[a.x][a.y])
        return false;
    return true;
}

int bfs()
{
    int ans = 0;
    queue<Node> q;
    Node node, newNode;
    q.push(s);
    inQueue[s.x][s.y] = true;
    while (!q.empty())
    {
        node = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            newNode.x = node.x+dx[i];
            newNode.y = node.y+dy[i];
            if (judge(newNode))
            {
                if (newNode.x == t.x && newNode.y == t.y)
                    return node.dis+1;
                
                newNode.dis = node.dis+1;
                inQueue[newNode.x][newNode.y] = true;
                q.push(newNode);
            }
        }
    }
    return -1;
}

int main()
{
    scanf("%d %d", &M, &N);

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            scanf("%c", &maze[i][j]);
            if (maze[i][j]=='S')
            {
                s.x = i;
                s.y = j;
            }else if (maze[i][j]=='T')
            {
                t.x = i;
                t.y = j;
            }
        }
        getchar();  //吃回车
    }

    printf("%d\n", bfs());
    
    return 0;
}