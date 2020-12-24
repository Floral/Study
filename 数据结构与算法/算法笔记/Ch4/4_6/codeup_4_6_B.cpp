#include<cstdio>
#include<algorithm>
#define maxn 100005

int arr[maxn] = {0};
int temp[maxn] = {0};

void merge(int L1, int R1, int L2, int R2)
{
    int index = 0;
    int i = L1, j = L2;
    while (i <= R1 && j <= R2)
    {
        if (arr[i] <= arr[j])
            temp[index++] = arr[i++];
        else
            temp[index++] = arr[j++];
        
    }

    while (i <= R1)
        temp[index++] = arr[i++];
    while (j <= R2)
        temp[index++] = arr[j++];
    for (int i = 0; i < index; i++)
        arr[L1+i] = temp[i];
}

void mergeSort(int L, int R)
{
    if (L < R)
    {
        int mid = (L+R)/2;
        mergeSort(L, mid);
        mergeSort(mid+1, R);

        merge(L, mid, mid+1, R);
    }
}

void mergeSortNoRecursion(int L, int R)
{
    int n = R-L+1;
    int mid;
    for (int step = 2; step/2 <= n; step*=2)    //一组的步长
    {
        for (int i = 0; i <= n; i+=step)    //第i/step组
        {
            mid = L+i+step/2-1;
            merge(L+i, mid, mid+1, std::min(L+i+step-1, R));
        }
    }
}

int main()
{
    int n, m;

    scanf("%d", &n);
    while (n--)
    {
        scanf("%d", &m);
        for (int i = 0; i < m; i++)
        {
            scanf("%d", arr+i);
        }

        mergeSortNoRecursion(0, m-1);

        for (int i = 0; i < m; i++)
        {
            printf("%d\n", arr[i]);
        }
        
    }

    return 0;
}