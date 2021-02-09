#include<cstdio>
#include<cstring>
#define maxn 105

char str[maxn];
struct Node
{
    char data;
    Node* left;
    Node* right;
};

Node* newNode(char data)
{

    Node* ret = new Node;
    ret->data = data;
    ret->left = nullptr;
    ret->right = nullptr;
    return ret;
}

void create(Node* &root, char data[], int &pos, int sz) //! 这个pos有必要变成引用，不然会导致节点重复
{
    if (pos >= sz)
        return ;
    if (data[pos]=='#')
        return ;
    root = newNode(data[pos]);
    create(root->left, data, ++pos, sz);
    create(root->right, data, ++pos, sz);
}

void inorder(Node* root)
{
    if (root==nullptr)
        return;
    inorder(root->left);
    printf("%c ", root->data);
    inorder(root->right);
}

int main()
{
    int s = 0;
    while (scanf("%s", str)!=EOF)
    {
        s = 0;
        Node* root = nullptr;
        create(root, str, s, strlen(str));
        inorder(root);
        putchar('\n');
    }

    return 0;
}