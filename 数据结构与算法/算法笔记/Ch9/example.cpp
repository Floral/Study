#include<cstdio>
#define maxn 10

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

void insert(Node* &root, int data)
{
    if (root==nullptr)
    {
        root = newNode(data);
        return ;
    }
    
    if (data <= root->data)
        insert(root->left, data);
    else
        insert(root->right, data);
}

Node* createTree(int data[], int n)
{
    Node* root = nullptr;
    for (int i = 0; i < n; i++)
    {
        insert(root, data[i]);
    }
    return root;
}

int preSeq[maxn];
int inSeq[maxn];

Node* createTreeFromPreAndIn(int preL, int preR, int inL, int inR)
{
    Node* root = nullptr;
    if (preL <= preR)
    {
        root = newNode(preSeq[preL]);
        int k;
        for (k = inL; k <= inR; k++)
        {
            if (inSeq[k]==preSeq[preL])
                break;
        }
        int numOfLeftTree = k-inL;
        if (k!=inR) //* 这个判断是多余的
        {
            root->left = createTreeFromPreAndIn(preL+1, preL+numOfLeftTree, inL, k-1);
            root->right = createTreeFromPreAndIn(preL+numOfLeftTree+1, preR, k+1, inR);
        }
    }

    return root;
}

int main()
{

    return 0;
}