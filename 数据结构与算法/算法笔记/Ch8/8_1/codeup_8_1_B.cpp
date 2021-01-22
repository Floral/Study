#include<cstdio>
#include<vector>

using namespace std;

vector<int> arr;

int N, r;

void combination(int index, int start)
{
    if (index == r)
    {
        for (int i = 0; i < arr.size(); i++)
            printf("%d ", arr[i]);
        putchar('\n');
        return ;
    }
    
    for (int i = start; i <= N; i++)
    {
        arr.push_back(i);
        combination(index+1, i+1);
        arr.pop_back();
    }
}

void combination()
{
    for (int i = 1; i <= N; i++)
    {
    }
}

int main()
{
    while (scanf("%d %d", &N, &r)!=EOF)
        combination(0, 1);

    return 0;
}