#include<cstdio>
#include<algorithm>
#define maxn 200005

int arr1[maxn] = {0};
int arr2[maxn] = {0};

int median(int arr1[], int arr2[], int N1, int N2)
{
    int index1 = 0, index2 = 0;
    int mid = (N1+N2)/2 + (N1+N2)%2;
    int count = 0;
    while (index1 < N1 && index2 < N2)
    {
        if (arr1[index1] <= arr2[index2])
        {
            index1++;
            count++;
            if (count == mid)
                return arr1[index1-1];
        }else
        {
            index2++;
            count++;
            if (count == mid)
                return arr2[index2-1];
        }
    }

    while (index1 < N1)
    {
        index1++;
        count++;
        if (count == mid)
            return arr1[index1-1];
    }
    
    while (index2 < N2)
    {
        index2++;
        count++;
        if (count == mid)
            return arr2[index2-1];
    }
    return -1;
}

int main()
{
    int N1, N2;

    scanf("%d", &N1);
    for (int i = 0; i < N1; i++)
    {
        scanf("%d", arr1+i);
    }
    
    scanf("%d", &N2);
    for (int i = 0; i < N2; i++)
    {
        scanf("%d", arr2+i);
    }

    int res = median(arr1, arr2, N1, N2);
    if (res!=-1)
    {
        printf("%d\n", res);
    }
    
    return 0;
}