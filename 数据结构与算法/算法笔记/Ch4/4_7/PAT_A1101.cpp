#include<cstdio>
#include<algorithm>
#define maxn 100005

int arr[maxn] = {0};
int copy[maxn] = {0};

int main()
{
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; i++)
    {
        scanf("%d", arr+i);
        copy[i] = arr[i];
    }

    std::sort(copy, copy+N);

    int count = 0, leftMax = 0;
    //version 1, 这里想的是，只要位置没有变就一定是主元，但是我忽略了一个事实就是，
    //即使排序后位置没变，但是它原来的左侧也可能有大于它的数，右侧也可能有小于它的数
    for (int i = 0; i < N; i++)
    {
        //这两行是原版，逻辑不完整
        // if (copy[i] == arr[i])
            // res[count++] = arr[i];
        //以下是修改版
        if (copy[i] == arr[i] && arr[i]>leftMax)
            copy[count++] = arr[i];
        if (arr[i] > leftMax)
            leftMax = arr[i];
    }

    printf("%d\n", count);
    for (int i = 0; i < count; i++)
    {
        if (i!=0)
            printf(" ");
        printf("%d", copy[i]);
    }
    putchar('\n');

    return 0;
}

/*
//以下是方案二
int arr[maxn] = {0};
int leftMax[maxn] = {0};
int rightMin[maxn] = {0};
int ans[maxn] = {0};

int main()
{
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; i++)
    {
        scanf("%d", arr+i);
    }

    int max = 0;
    leftMax[0] = 0;
    for (int i = 1; i < N; i++)
    {
        if (arr[i-1]>max)
        {
            max = arr[i-1];
            leftMax[i] = max;
        }else
        {
            leftMax[i] = leftMax[i-1];
        }
        //以下是优化版
        //leftMax[i] = std::max(arr[i-1], leftMax[i-1]);
    }

    int min = (1<<31)-1;
    rightMin[N-1] = min;
    for (int i = N-2; i >= 0; i--)
    {
        if (arr[i+1]<min)
        {
            min = arr[i+1];
            rightMin[i] = min;
        }else
        {
            rightMin[i] = rightMin[i+1];
        }
        //以下是优化版
        //rightMin[i] = std::min(arr[i+1], rightMin[i+1]);
    }
    int count = 0;
    for (int i = 0; i < N; i++)
    {
        if (arr[i] > leftMax[i] && arr[i] < rightMin[i])
            ans[count++] = arr[i];
    }
    
    printf("%d\n", count);
    for (int i = 0; i < count; i++)
    {
        if (i!=0)
            printf(" ");
        printf("%d", ans[i]);
    }
    putchar('\n');
    return 0;
}
*/