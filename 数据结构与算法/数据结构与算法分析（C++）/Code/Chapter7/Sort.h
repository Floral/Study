#ifndef MY_SORT
#define MY_SORT

#include<vector>
#include<utility>
#include<functional>

//STL版插入排序
template<typename Iterator>
void insertionSort(const Iterator& begin, const Iterator& end)
{
    insertionSort(begin, end, std::less<decltype(*begin)>{});
}

template<typename Iterator, typename Comparator>
void insertionSort(const Iterator& begin, const Iterator& end, Comparator lessThan)
{
    if (begin == end)
        return;
    
    Iterator j;

    for (Iterator p = begin+1; p != end; ++p)
    {
        auto key = std::move(*p);
        for ( j = p-1; j != begin && lessThan(key, *j) ; --j)
            *(j+1) = std::move(*j);

        *(j+1) = std::move(key);
    }
}

//希尔排序（Shellsort）
//也叫缩减增量排序，其实就是插入排序修改了交换元素的间隔(就是增量)
//插入排序是相邻的交换，希尔排序是间隔由大变小，多轮交换，直到间隔为1（也就是相邻）
template<typename T>
void shellSort(std::vector<T>& a)
{
    for (int gap = a.size()/2; gap >= 1; gap/=2)
    {
        for (int i = gap; i < a.size(); ++i)
        {
            auto key = std::move(a[i]);
            int p;

            for (p = i; p >= 0 && key < a[p-gap]; p-=gap)
                a[p] = std::move(a[p-gap]);
            a[p] = std::move(key);
        }
    }
}

//
//堆排序
//
template<typename T>
void heapSort(std::vector<T>& a)
{
    for (size_t i = a.size()/2; i >= 0 ; --i)   //在原数组的基础上build heap
        percDown(a, i, a.size());   
    for (size_t i = a.size()-1; i > 0; --i)     ///deleteMin
    {
        std::swap(std::move(a[0]), std::move(a[i]));
        percDown(a, 0, i);
    }
}

//返回下表为i的左孩子的下标
inline int leftChild(int i)
{
    return 2*i + 1; //这里加一是因为我们这里的堆是以0为开始的标号
}

//  i是要下滤的位置
//  n是数组的大小
template<typename T>
void percDown(std::vector<T>& a, int i, int n)
{
    int child;
    T key;
    for (key = std::move(a[i]); leftChild(i) < n; i = child)
    {
        child = leftChild(i);
        if (child != n && a[child+1] < a[child])
            ++child;
        if (key < a[child])
            a[i] = std::move(a[child]);
        else
            break;
    }
    a[i] = std::move(key);
}

template<typename T>
void mergeSort(std::vector<T>& a)
{
    std::vector<T> tmpArray(a.size());
    mergeSort(a, tmpArray, 0, a.size()-1);
}

template<typename T>
void mergeSort(std::vector<T>& a, std::vector<T>& tmpArray, int left, int right)
{
    if (left < right)
    {
        int center = (left + right)/2;
        mergeSort(a, tmpArray, left, center);
        mergeSort(a, tmpArray, center+1, right);
        merge(a, tmpArray, left, center+1, right);
    }
}

template<typename T>
void merge(std::vector<T>& a, std::vector<T>& tmpArray, 
           int leftPos, int rightPos, int rightEnd)
{
    int leftEnd = rightPos - 1;
    int tmpPos = leftPos;
    int numElements = rightEnd - leftPos + 1;

    while (leftPos <= leftEnd && rightPos <= rightEnd)  //只要有一个被合并的数组“跑完了”就可以只用跑剩下的另一个了，就不用if-else了
    {
        if (a[leftPos] <= a[rightPos])
            tmpArray[tmpPos++] = std::move(a[leftPos++]);
        else
            tmpArray[tmpPos++] = std::move(a[rightPos++]);
    }

    while (leftPos <= leftEnd)
        tmpArray[tmpPos++] = std::move(a[leftPos++]);

    while (rightPos <= rightEnd)
        tmpArray[tmpPos++] = std::move(a[rightPos++]);
    
    //把临时数组的数复制到原数组a
    for (size_t i = 0; i < numElements; ++i, --rightEnd)
        a[rightEnd] = std::move(tmpArray[rightEnd]);    
        //这里不能用i来当下标的原因是合并数组会发生在原数组a的中间，只有在最后一次合并的时候才是整个数组的大小。
}


#endif