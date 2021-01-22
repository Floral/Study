#include<cstdio>
#include<queue>

using namespace std;

int main()
{
    int arr[10];
    int minPos = 0, maxPos = 0;
    queue<int> q;

    for (int i = 0; i < 10; i++)
    {
        scanf("%d", arr+i);
        if (arr[i]>arr[maxPos])
            maxPos = i;
        if (arr[i]<arr[minPos])
            minPos = i;
    }
    int min = arr[minPos], max = arr[maxPos];
    arr[minPos] = arr[0];
    arr[maxPos] = arr[9];
    //! 并没有实现 换位 这个功能
    q.push(min);
    for (int i = 1; i < 9; i++)
    {
        // if (i!=minPos && i!=maxPos)
            q.push(arr[i]);
    }
    q.push(max);
    
    while (!q.empty())
    {
        printf("%d ", q.front());
        q.pop();
    }
    return 0;
}
