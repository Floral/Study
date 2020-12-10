#include<cstdio>
#include<algorithm>

int arr[1010] = {0};

int main(){
    int N;

    while (scanf("%d", &N)!=EOF)
    {
        for (size_t i = 0; i < N; i++)
        {
            scanf("%d", arr+i);
        }
        
        std::sort(arr, arr+N);

        printf("%d\n", arr[N-1]);
        if (N>1)
        {
            for (size_t i = 0; i < N-1; i++)
            {
                printf("%d",arr[i]);
                if (i<N-2)
                {
                    printf(" ");
                }else
                {
                    printf("\n");
                }
            }
        }else
        {
            printf("-1\n");
        }
    }

    return 0;
}