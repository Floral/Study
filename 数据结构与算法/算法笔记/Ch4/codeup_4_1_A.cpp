#include<cstdio>
#include<algorithm>

int arr[110] = {0};

int main()
{
    int n;

    while (scanf("%d",&n)!=EOF)
    {
        for (size_t i = 0; i < n; i++)
        {
            scanf("%d", arr+i);
        }

        std::sort(arr, arr+n);
        
        for (size_t i = 0; i < n; i++)
        {
            printf("%d", arr[i]);
            if (i<n-1)
            {
                printf(" ");
            }
        }
    }

    return 0;
}