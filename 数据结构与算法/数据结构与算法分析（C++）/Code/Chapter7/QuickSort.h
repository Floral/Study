#ifndef MY_QUICK_SORT
#define MY_QUICK_SORT

#include<iostream>
#include<vector>
#include<utility>
#include"Sort.h"

template<typename T>
void quickSort(std::vector<T>& a, int left, int right);

template<typename T>
void quickSort(std::vector<T>& a)
{
    quickSort(a, 0, a.size()-1);
}

template<typename T>
const T& median3(std::vector<T>& a, int left, int right)
{
    int center = (left+right)/2;

    if (a[center] < a[left])
        std::swap(a[left], a[center]);
    if (a[right] < a[left])
        std::swap(a[right], a[left]);
    if (a[right] < a[center])
        std::swap(a[right], a[center]);

    //将枢纽元放在right-1处，因为经过上面的操作right已经比枢纽元大了，就节省一个判断
    std::swap(a[center], a[right-1]);
    return a[right-1];
}

template<typename T>
void quickSort(std::vector<T>& a, int left, int right)
{
    if (left+10 <= right)   //N太小小的话直接插入排序的效率比较高
    {
        const T& pivot = median3(a, left, right);

        //开始分割
        int i = left, j = right-1;
        while (1)
        {
            while (a[++i] < pivot) {}
            while (pivot < a[--j]) {}
            if (i < j)
                std::swap(a[i], a[j]);
            else
                break;
        }
        
        std::swap(a[i], a[right-1]);    //恢复枢纽元的位置

        //递归处理子序列
        quickSort(a, left, i-1);
        quickSort(a, i+1, right);

        
    }
    else
        insertionSort(std::begin(a), std::end(a));
    
}

#endif