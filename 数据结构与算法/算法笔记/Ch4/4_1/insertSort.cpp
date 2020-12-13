#include<cstdio>


void insertSort(int* first, int n){
    int temp = 0;
    for (size_t i = 1; i < n; i++)
    {
        temp = first[i];
        // for (size_t j = i-1; j >= 0; j--)
        // {
        //     if (temp < first[j])
        //     {
        //         first[j+1] = first[j];
        //     }else
        //     {
        //         first[j+1] = temp;
        //         break;
        //     }
        // }

        size_t j = i-1;
        for (j = i-1; j >= 0 && temp < first[j]; j--)
        {
            first[j+1] = first[j];
        }
        first[j+1] = temp;
    }
}

int main(){
    
    int a[6] = {5,2,4,6,3,1};

    insertSort(a, 6);

    for (size_t i = 0; i < 6; i++)
    {
        printf("%d ", a[i]);
    }
    
    return 0;
}