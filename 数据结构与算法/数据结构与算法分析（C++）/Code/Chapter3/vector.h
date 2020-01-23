#ifndef VECTOR
#define VECTOR

#include<algorithm>

template <typename Object>
class Vector
{
private:
    /* data */
    int theSize;    //vector元素数目
    int theCapacity;    //当前vector最大容量
    Object* objects;    //vector内部数据

public:
    typedef Object* iterator;
    typedef const Object* const_iterator;
    static const int SPARE_CAPACITY = 16;
    Vector(int initSize = 0);
    Vector(const Vector& rhs);  //拷贝构造函数
    Vector(Vector&& rhs);       //移动构造函数
    ~Vector(){ delete [] objects;}
    Vector& operator=(const Vector& rhs);   //拷贝赋值函数
    Vector& operator=(Vector&& rhs);        //移动赋值函数

    Object& operator[](int index);
    const Object& operator[](int index) const;

    int size() const {return theSize; }   //返回vector大小
    int capacity() const { return theCapacity; }
    void reserve(int newCapacity);      //重新分配数组的容量大小
    void resize(int newSize);
    bool empty() const { return theSize ? false:true; }

    void push_back(const Object& x);
    void push_back(Object&& x);
    void pop_back();                    //弹出最后一个元素，但是不返回其值
    const Object& back() const;         //访问最后一个元素的值，返回引用是为了避免复制

    iterator begin() {return &objects[0];}
    const_iterator begin() const {return &objects[0];}
    iterator end() {return &objects[size()];}
    const_iterator end() const {return &objects[size()];}

};

template<typename Object>
Vector<Object>::Vector(int initSize):   //默认值在声明的时候
theSize{initSize}, theCapacity{initSize+SPARE_CAPACITY}
{ 
    objects = new Object[theCapacity];
}

template<typename Object>   //拷贝构造函数实现
Vector<Object>::Vector(const Vector<Object>& rhs):
theSize{rhs.theSize}, theCapacity{rhs.theCapacity}, objects{nullptr}
{
    objects = new Object[theCapacity];
    for (size_t i = 0; i < theSize; ++i)
    {
        objects[i] = rhs.objects[i];
    }
}

template<typename Object>
Vector<Object>::Vector(Vector&& rhs):
theSize{rhs.theSize}, theCapacity{rhs.theCapacity}, objects{rhs.objects}    //直接复制指针的值
{
    rhs.objects = nullptr;
    rhs.theSize = 0;
    rhs.theCapacity = 0;
}

template<typename Object>
Vector<Object>& Vector<Object>::operator=(const Vector& rhs)
{
    Vector copy = rhs;  //这里调用了Vector的拷贝构造函数
    std::swap(*this, copy);
    return *this;
}
template<typename Object>
Vector<Object>& Vector<Object>::operator=(Vector&& rhs)
{
    std::swap(theSize, rhs.theSize);
    std::swap(theCapacity, rhs.theCapacity);
    std::swap(objects, rhs.objects);
    return *this;
}

template<typename Object>
Object& Vector<Object>::operator[](int index)
{   return objects[index];  }

template<typename Object>
const Object& Vector<Object>::operator[](int index) const
{   return objects[index];  }

template<typename Object>
void Vector<Object>::reserve(int newCapacity)
{
    if (newCapacity < theCapacity)
    {
        theCapacity = newCapacity;
        return;
    }
    Object* newArray = new Object[newCapacity];
    for (size_t i = 0; i < theSize; ++i)
        newArray[i] = std::move(objects[i]);    //移动赋值
    
    theCapacity = newCapacity;
    std::swap(objects, newArray);               //直接交换指针的值
    delete [] newArray;
}

template<typename Object>
void Vector<Object>::resize(int newSize)
{
    if (newSize > theCapacity)
        reserve(newSize*2);
    theSize = newSize;
}

template<typename Object>
void Vector<Object>::push_back(const Object& x)
{
    if (theSize == theCapacity)
        reserve(theCapacity*2+1);
    objects[theSize++] = x;
}

template<typename Object>
void Vector<Object>::push_back(Object&& x)
{
    if (theSize == theCapacity)
        reserve(theCapacity*2+1);
    objects[theSize++] = std::move(x);
}

template<typename Object>
void Vector<Object>::pop_back()
{
    --theSize;
}

template<typename Object>
const Object& Vector<Object>::back() const
{
    return objects[theSize-1];
}

#endif