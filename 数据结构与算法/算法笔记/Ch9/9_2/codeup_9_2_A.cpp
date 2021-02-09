#include<cstdio>
#include<string>
#include<iostream>
#define maxn 10

using namespace std;

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

string s1, s2;

Node* createTreeFromPreAndIn(int preL, int preR, int inL, int inR)
{
    Node* root = nullptr;
    if (preL <= preR)
    {
        root = newNode(s1[preL]);
        int k;
        for (k = inL; k <= inR; k++)
        {
            if (s2[k]==s1[preL])
                break;
        }
        int numOfLeftTree = k-inL;
        // if (k!=inR) //* 这个判断是多余的
        // {
            root->left = createTreeFromPreAndIn(preL+1, preL+numOfLeftTree, inL, k-1);
            root->right = createTreeFromPreAndIn(preL+numOfLeftTree+1, preR, k+1, inR);
        // }
    }

    return root;
}

void postOrder(Node* root)
{
    if (root==nullptr)
        return;

    // printf("%d", root->data);
    postOrder(root->left);
    postOrder(root->right);
    printf("%c", root->data);
}

int main()
{
    Node* root;
    while (cin>>s1>>s2)
    {
        root = createTreeFromPreAndIn(0, s1.size()-1, 0, s2.size()-1);
        postOrder(root);
        putchar('\n');
        //* 严格来说要把这root整个树delete掉，不然会内存泄漏
    }
    
    return 0;
}