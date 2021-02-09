#include<cstdio>
#include<queue>
#define maxn 32
using namespace std;
int postSeq[maxn];
int inSeq[maxn];

struct Node
{
    int data;
    Node* left;
    Node* right;
};

Node* newNode(int data)
{
    Node* ret = new Node;
    ret->data = data;
    ret->left = nullptr;
    ret->right = nullptr;
    return ret;
}

Node* createTreeFromPostAndIn(int postL, int postR, int inL, int inR)
{
    if (postL > postR)
        return nullptr;

    Node* root = newNode(postSeq[postR]);
    int k;
    for (k = inL; k <= inR; k++)
    {
        if (inSeq[k]==postSeq[postR])
            break;
    }
    int numLeft = k-inL;
    root->left = createTreeFromPostAndIn(postL, postL+numLeft-1, inL, k-1);
    root->right = createTreeFromPostAndIn(postL+numLeft, postR-1, k+1, inR);

    return root;
}

// void postOrder(Node* root)
// {
//     if (root==nullptr)
//         return;

//     // printf("%d", root->data);
//     postOrder(root->left);
//     postOrder(root->right);
//     printf("%d", root->data);
// }
void levelOrder(Node* root)
{
    if (root==nullptr)
        return;
    Node* now = nullptr;
    queue<Node*> q;
    q.push(root);

    while (!q.empty())
    {
        now = q.front();
        q.pop();
        if (now!=root)
            putchar(' ');
        printf("%d", now->data);

        if (now->left!=nullptr)
            q.push(now->left);
        if (now->right!=nullptr)
            q.push(now->right);
    }
}

int main()
{
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; i++)
        scanf("%d", &postSeq[i]);
    
    for (int i = 0; i < N; i++)
        scanf("%d", &inSeq[i]);

    Node* root = createTreeFromPostAndIn(0, N-1, 0, N-1);
    levelOrder(root);

    return 0;
}