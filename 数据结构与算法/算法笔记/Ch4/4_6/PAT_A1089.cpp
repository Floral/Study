#include<cstdio>
#include<algorithm>
#define maxn 105

int orig[maxn] = {0};
int tArr[maxn] = {0};
int proc[maxn] = {0};

bool cmpArr(int arr1[], int arr2[], int left, int right)
{
    bool res = true;
    for (int i = left; i <= right; i++)
    {
        if (arr1[i]!=arr2[i])
        {
            res = false;
            break;
        }
    }
    return res;
}

void printArr(int arr[], int left, int right)
{
    for (int i = left; i <= right; i++)
    {
        if (i!=right)
            printf("%d ", arr[i]);
        else
            printf("%d", arr[i]);
    }
    putchar('\n');
}

bool insertSort(int arr[], int left, int right)
{
    int temp;
    bool flag = false, lastFlag = false;    //bool类型默认值是true,所以不要忘了初始化
    for (int i = left+1; i <= right; i++)
    {
        //这一段是书上的写法
        // if (i!=left+1 && cmpArr(arr, proc, left, right))
            // flag = true;
        
        temp = arr[i];
        int j;
        for (j = i; j > left && arr[j-1] > temp; j--)
            arr[j] = arr[j-1];
        arr[j] = temp;

        //这一段是书上的写法，经过上面的for循环就得到了下一轮的结果，所以不需要两个flag了，比较巧妙
        // if (flag)
        // {
        //     printf("Insertion Sort\n");
        //     printArr(arr, left, right);
        //     return true;
        // }

        flag = cmpArr(arr, proc, left, right);
        if (flag == true)
            printf("Insertion Sort\n");
        if (lastFlag && !flag)  //我这设置两个flag是为了得到下一轮的结果,不过看了书上的答案之后觉得书上的方法更好
        {
            printArr(arr, left, right);
            return true;
        }
        lastFlag = flag;
    }
    return false;
}

void merge(int arr[], int L1, int R1, int L2, int R2)
{
    int temp[maxn] = {0};
    int index = 0, start = L1;
    while (L1 <= R1 && L2 <= R2)
    {
        if (arr[L1] <= arr[L2])
            temp[index++] = arr[L1++];
        else
            temp[index++] = arr[L2++];
    }
    while (L1<=R1)
        temp[index++] = arr[L1++];
    while (L2<=R2)
        temp[index++] = arr[L2++];
    
    for (int i = 0; i < index; i++)
        arr[start+i] = temp[i];
}

void mergeSort(int arr[], int left, int right)
{
    int n = right-left+1;
    int mid;
    bool flag = false, lastFlag = false;
    for (int step = 2; step/2 <= n; step*=2)
    {
        //同insertion sort
        // if (step!=2 && cmpArr(arr, proc, left, right))
            // flag = true;
        
        for (int i = 0; i <= n; i+=step)
        {
            mid = left+i+step/2-1;
            merge(arr, left+i, mid, mid+1, std::min(right, left+i+step-1));
        }

        //同insertion sort
        // if (flag)
        // {
        //     printf("Merge Sort\n");
        //     printArr(arr, left, right);
        //     break;
        // }

        flag = cmpArr(arr, proc, left, right);
        if (flag)
            printf("Merge Sort\n");
        if (lastFlag && !flag)
        {
            printArr(arr, left, right);
            break;
        }
        lastFlag = flag;
    }
}

int main()
{
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
    {
        scanf("%d", orig+i);
        tArr[i] = orig[i];
    }
    for (int i = 0; i < N; i++)
    {
        scanf("%d", proc+i);
    }

    if (!insertSort(tArr, 0, N-1))
        mergeSort(orig, 0, N-1);

    return 0;
}