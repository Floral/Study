#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<cmath>
#define maxn 1000005

int arr[maxn] = {0};

int randPartion(int arr[], int left, int right)
{
    int p = round(1.0*rand()/RAND_MAX*(right-left)+left);
    std::swap(arr[p], arr[left]);

    int pivot = arr[left];
    while (left<right)
    {
        while (left<right && arr[right]<=pivot) //因为找的是第k大的，所以从大到小排
            right--;
        arr[left] = arr[right];
        while (left<right && arr[left]>pivot)
            left++;
        arr[right] = arr[left];
    }
    
    arr[left] = pivot;
    return left;
}

int findKth(int arr[], int left, int right, int k)
{
    if (left<right)
    {
        int p = randPartion(arr, left, right);
        int M = p-left+1;
        if (M==k)
            return arr[p];
        if (M > k)
            return findKth(arr, left, p-1, k);
        else
            return findKth(arr, p+1, right, k-M);
    }
    return arr[left];   //就一个数，还找啥
}

int main()
{
    int n, k;

    srand((unsigned)time(NULL));    //不知道为啥codeup oj加上这句话就过不了了
    scanf("%d %d", &n, &k);
    
    for (int i = 0; i < n; i++)
        scanf("%d", arr+i);

    int ans = findKth(arr, 0, n-1, k);
    printf("%d\n", ans);

    return 0;
}