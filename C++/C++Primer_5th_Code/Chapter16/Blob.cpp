#include"Bolb.h"

template<typename T>
Blob<T>::Blob(): data(std::make_shared<std::vector<T>>()) {}

template<typename T>
Blob<T>::Blob(std::initializer_list<T> il):
        data(std::make_shared<std::vector<T>>(il)) {}


template<typename T>
void Blob<T>::check(size_type i, const std::string &msg) const
{
    if(i>=data->size())
        throw std::out_of_range(msg);
}

template<typename T>
T& Blob<T>::back()
{
    check(0, "back on empty Blob");
    return data->back();
}

template<typename T>
T& Blob<T>::operator[](size_type i)
{
    check(i, "subscript out of range");
    return (*data)[i];
}

template<typename T>
void Blob<T>::pop_back()
{
    check(0, "pop_back on empty Blob");
    data->pop_back();
}

//=============== BlobPtr =================
template<typename T>
BlobPtr<T> BlobPtr<T>::operator++(int)
{
    BlobPtr ret = *this;
    ++*this;
    return ret;
}

template<typename T>
BlobPtr<T> BlobPtr<T>::operator--(int)
{
    BlobPtr ret = *this;
    --*this;
    return ret;
}
