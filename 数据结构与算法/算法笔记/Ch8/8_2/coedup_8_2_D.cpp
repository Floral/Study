#include<cstdio>
#include<string>
#include<queue>
#include<map>
using namespace std;

struct Node
{
    int board[2][4];
    int step = 0;
    string path;
};

char dir[3] = {'A', 'B', 'C'};

Node nextNode(const Node &pre, char op)
{
    Node ret = pre;
    if (op=='A')
    {
        for (int i = 0; i < 4; i++)
        {
            ret.board[0][i] = pre.board[1][i];
            ret.board[1][i] = pre.board[0][i];
        }
    }else if (op=='B')
    {
        for (int i = 0; i < 4; i++)
        {
            ret.board[0][i] = pre.board[0][(i+3)%4];
            ret.board[1][i] = pre.board[1][(i+3)%4];
        }
    }else if (op=='C')
    {
        ret.board[0][1] = pre.board[1][1];
        ret.board[1][1] = pre.board[1][2];
        ret.board[1][2] = pre.board[0][2];
        ret.board[0][2] = pre.board[0][1];
    }
    ret.path = pre.path+op;
    ret.step = pre.step+1;
    
    return ret;
}

int board2int(const int board[2][4])
{
    int ans=0;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 4; j++)
            ans = ans*10+board[i][j];
    return ans;
}

int bfs(Node pre,Node &aim)
{
    int ans = 0;
    queue<Node> q;
    map<int, bool> hashMp;

    q.push(pre);
    hashMp[board2int(pre.board)] = true;
    int aimFlag = board2int(aim.board);
    while (!q.empty())
    {
        pre = q.front();
        q.pop();
        if (board2int(pre.board)==aimFlag)
        {
            aim.path = pre.path;
            aim.step = pre.step;
            return pre.step;
        }
        for (int i = 0; i < 3; i++)
        {
            Node next = nextNode(pre, dir[i]);
            int key = board2int(next.board);
            if (hashMp[key]==false)
            {
                hashMp[key] = true;
                q.push(next);
            }
        }
    }
    return ans;
}

int main()
{
    Node init, aim;
    
    for (int i = 0; i < 4; i++)
    {
        scanf("%d", &aim.board[0][i]);
        init.board[0][i] = i+1;
    }
    
    for (int i = 3; i >= 0; i--)
    {
        scanf("%d", &aim.board[1][i]);
        init.board[1][i] = 8-i;
    }

    int ans = bfs(init, aim);
    printf("%d\n", ans);
    int left = aim.step;
    int startPos = 0;
    while (left >= 60)
    {
        printf("%s\n", aim.path.substr(startPos, 60).c_str());
        startPos+=60;
        left-=60;
    }
    if (left>0)
        printf("%s\n", aim.path.substr(startPos, left).c_str());

    return 0;
}