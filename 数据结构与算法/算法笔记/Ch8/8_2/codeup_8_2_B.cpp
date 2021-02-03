#include<cstdio>
#include<vector>
#include<queue>
#define M 8
#define N 8
using namespace std;

struct Node
{
    int x, y;
    int step = 0;
};

char maze[M][N];
int dx[9] = {0, -1, 1, 0, 0, -1, -1, 1, 1};
int dy[9] = {0, 0, 0, -1, 1, -1, 1, -1, 1};
int highest = 0;
//! 对比这个blog吧:https://blog.csdn.net/qq_42819248/article/details/81673815
bool judge(const Node &node)    //* 注意node是已经走了step步后的坐标
{
    if (node.x<0 || node.x>=M || node.y<0 || node.y>=N)
        return false;
    else if (node.x-node.step>=0 && //! 不知道为什么加了这一个条件就错....
            (maze[node.x-node.step][node.y]=='S' ||     //* node.x-node.step是判断走了之后上一格是不是石头
             maze[node.x-node.step+1][node.y]=='S'))    //* node.x-node.step+1是判断走到的那一格是不是石头
        return false;
    
    return true;
}
bool solve()
{
    Node U, t;
    queue<Node> q;
    U.x = M-1, U.y = 0;
    bool ans = false;

    q.push(U);
    while (!q.empty())
    {
        U = q.front();
        q.pop();
        for (int i = 0; i < 9; i++)
        {
            t.x = U.x+dx[i];
            t.y = U.y+dy[i];
            t.step = U.step+1;
            if (judge(t))
            {
                if (maze[t.x][t.y]=='A' || t.step>=8-highest)
                    return true;
                q.push(t);
            }
        }
    }
    
    return ans;
}
//* dfs做法：https://blog.csdn.net/qq_44854593/article/details/105916863
int main()
{
    int n;
    bool ans, flag = true;
    scanf("%d", &n);
    getchar();
    for (int t = 1; t <= n; t++)
    {
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                scanf("%c", &maze[i][j]);
                if (flag && maze[i][j]=='S')
                {
                    flag = false;
                    highest = i;    //记录最高的石头
                }
            }
            getchar();  //吃回车
        }
        ans = solve();
        if (ans)
            printf("Case #%d: Yes\n", t);
        else
            printf("Case #%d: No\n", t);
        getchar();
    }
    
    return 0;
}