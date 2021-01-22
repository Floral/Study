#include<cstdio>

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int main()
{
    int arr[10];
    int minPos = 0, maxPos = 0;

    for (int i = 0; i < 10; i++)
    {
        scanf("%d", arr+i);
        if (arr[i]>arr[maxPos])
            maxPos = i;
        //* else if (arr[i]<arr[minPos])
        //*     minPos = i;
    }
    //! 这种方法确实有bug,因为minPos可能就是9,maxPos可能就是0,经过两次交换之后又变回原样了
    //! 所以只能一次遍历得到minPos 或 maxPos，两次遍历交换两次
    //*******
    //* swap(arr[9], arr[maxPos]);
    //* swap(arr[0], arr[minPos]);
    //*******
    swap(arr[9], arr[maxPos]);
    
    for (int i = 0; i < 10; i++)
    {
        if (arr[i]<arr[minPos])
            minPos = i;
    }
    
    swap(arr[0], arr[minPos]);
    for (int i = 0; i < 10; i++)
        printf("%d ", arr[i]);
    
    return 0;
}