#include<cstdio>
#include<algorithm>
#define maxn 210

struct myData
{
    int x;
    int pos;    //保存位置信息
    bool operator<(const myData &b) const{  //这个方法也要加const，否则低版本的会报错
        return this->x < b.x;
    }
};

int findX(myData *arr, int left, int right, int x)
{
    int mid;

    while (left <= right)
    {
        mid = (left+right)/2;
        if (arr[mid].x == x)
            return arr[mid].pos;
        if (arr[mid].x > x)
            right = mid-1;
        else
            left = mid+1;
    }
    return -1;
}

int main()
{
    int n;
    myData arr[maxn] = {{0,0}};

    while (scanf("%d", &n)!=EOF)
    {
        int x;
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &arr[i].x);
            arr[i].pos = i;
        }
        scanf("%d", &x);

        std::sort(arr, arr+n);

        int ans = findX(arr, 0, n-1, x);
        printf("%d\n", ans);
    }
    
    return 0;
}