#include<cstdio>
#include<vector>

using namespace std;

vector<int> arr;
bool hashTable[11] = {false};

void fullPermutation(const int &N, int index)
{
    if (index == N) //N个数排列完了
    {
        printf("%d", arr[0]);
        for (int i = 1; i < arr.size(); i++)
            printf(" %d", arr[i]);
        putchar('\n');
        return ;
    }
    
    for (int i = 1; i <= N; i++)
    {
        if (!hashTable[i])
        {
            hashTable[i] = true;
            arr.push_back(i);
            fullPermutation(N, index+1);
            hashTable[i] = false;
            arr.pop_back();
        }
    }
}

int main()
{
    int N;

    while (scanf("%d", &N)!=EOF)
    {
        fullPermutation(N, 0);
    }

    return 0;
}