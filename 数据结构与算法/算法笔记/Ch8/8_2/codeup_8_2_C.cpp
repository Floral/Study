#include<cstdio>
#include<cstring>
#include<map>
#include<queue>
#define maxn 3
using namespace std;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

struct Node
{
    int x, y;
    int step = 1;
    int status[maxn][maxn]; 
    //! md，这里status之前是char类型，提交后死活过不了，不知道codeup的数据是什么鬼，改成int就行了
};
Node s, aim;

bool judge(const Node &a)
{
    if (a.x<0 || a.x>2 || a.y<0 || a.y>2)
        return false;
    return true;
}

int matrix2int(int status[maxn][maxn])
{
    int ans = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            ans = ans*10+status[i][j];
    return ans;
}

void copyM(char a[maxn][maxn], char b[maxn][maxn])
{
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            b[i][j] = a[i][j];
}

int bfs()
{
    queue<Node> q;
    map<int, bool> hashMp;
    int target = matrix2int(aim.status);
    int key = matrix2int(s.status);
    hashMp[key]=1;
    q.push(s);
    while (!q.empty())
    {
        s = q.front();
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            Node next = s;
            next.x = s.x+dx[i];
            next.y = s.y+dy[i];
            next.step = s.step+1;
            if (judge(next))
            {
                // copyM(s.status, next.status);
                swap(next.status[next.x][next.y], next.status[s.x][s.y]);
                int key = matrix2int(next.status);
                if (key == target)
                    return next.step;
                if (hashMp[key]==false)
                {
                    q.push(next);
                    hashMp[key]=true;
                }
            }
        }
    }
    return -1;
}

int main()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            scanf("%d", &s.status[i][j]);
            // getchar();  //吃空格和回车
            if (s.status[i][j]==0)
                s.x = i, s.y = j;
        }
    }

    int t;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            scanf("%d", &aim.status[i][j]);
            // getchar();  //吃空格和回车
            // scanf("%d", &t);
            // aim = aim*10+t;
        }
    }
    printf("%d\n", bfs());
    return 0;
}