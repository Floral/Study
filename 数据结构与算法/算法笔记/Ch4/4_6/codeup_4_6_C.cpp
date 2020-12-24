#include<cstdio>
#include<algorithm>
#define maxn 5005

int arr[maxn] = {0};
// https://blog.csdn.net/qq_36528114/article/details/78667034
int Partion(int arr[], int left, int right)
{
    //------------------双指针法-----------------
    int &pivot = arr[left];
    while (left < right)
    {
        //这种是双指针法,需要注意的是两个while的前后顺序
        //如果你的pivot是取的最左边,那么应该先从右指针开始往左移(如下)
        //如果你的pivot是取的最右边,那么应该先从左指针开始往右移
        //因为这两个while的循环条件都是等于,当pivot刚好是左端点且是最小值时候,
        //如果这时while left在前,那么就会导致left++,最终导致跳出最外层的while,
        //然后使得pivot与pivot+1位置的两个元素交换,然后就导致逻辑错误了.
        while (left<right && pivot <= arr[right]) --right;
        while (left<right && arr[left] <= pivot) ++left;
        if (left<right)
        {
            std::swap(arr[left], arr[right]);
        }
    }
    std::swap(pivot, arr[left]);
    // temp = arr[left];
    // arr[left] = pivot;
    // arr[first] = temp;
    // int pivot = arr[left];

    //----------------挖坑法--------------
    // int pivot=arr[left];

    // while (left<right)
    // {
    //     while (left<right && pivot <= arr[right])
    //         right--;
    //     arr[left] = arr[right];
    //     while (left<right && arr[left] <= pivot)
    //         left++;
    //     arr[right] = arr[left];
    // }
    
    // arr[left] = pivot;
    return left;
}

void qsort(int arr[], int L, int R)
{
    int pivot;
    if (L < R)
    {
        pivot = Partion(arr, L, R);
        qsort(arr, L, pivot-1);
        qsort(arr, pivot+1, R);
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", arr+i);
    }
    qsort(arr, 0, n-1);
    
    for (int i = 0; i < n; i++)
    {
        printf("%d\n", arr[i]);
    }
    
    return 0;
}