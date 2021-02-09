#include<cstdio>
#include<vector>
#include<algorithm>
#define maxn 105
using namespace std;

struct Node
{
    int data;
    vector<int> children;
}tree[maxn];
vector<int> path;

void dfs(int root, int sum, const int &weight)
{
    if (sum > weight)
        return;
    
    if (sum == weight && tree[root].children.size()==0)
    {
        printf("%d", path[0]);
        for (int i = 1; i < path.size(); i++)
            printf(" %d", path[i]);
        putchar('\n');
        return;
    }
    int child;
    // sum += tree[root].data;
    // path.push_back(tree[root].data);
    for (int i = 0; i < tree[root].children.size(); i++)
    {
        child = tree[root].children[i];
        path.push_back(tree[child].data);
        dfs(child, sum+tree[child].data, weight);
        path.pop_back();
    }
    // path.pop_back();
}
bool cmp(int a, int b)
{
    return tree[a].data > tree[b].data;
}

int main()
{
    int N, M, S;

    scanf("%d %d %d", &N, &M, &S);

    for (int i = 0; i < N; i++)
        scanf("%d", &tree[i].data);

    int t1, t2, k;
    for (int i = 0; i < M; i++)
    {
        scanf("%d %d", &t1, &k);
        for (int j = 0; j < k; j++)
        {
            scanf("%d",&t2);
            tree[t1].children.push_back(t2);
        }
        sort(tree[t1].children.begin(), tree[t1].children.end(), cmp);  
        //* 这个方法很nb，在输入的时候就把子节点的顺序排好，不然后面很难判断。
    }
    path.push_back(tree[0].data);
    dfs(0, tree[0].data, S);
    path.pop_back();
    return 0;
}