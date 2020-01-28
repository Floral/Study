#ifndef LIST
#define LIST

#include<algorithm>
#include<exception>

template<typename T>
class List
{
private:
    /* data */
    struct Node;
    Node* head;         //头节点
    Node* tail;         //尾节点
    int theSize;        //大小

    void init();

public:
    class const_iterator;
    class iterator;    

public:
    List();
    List(const List& rhs);  //以下是五大函数
    List(List&& rhs);
    ~List();
    List& operator=(const List& rhs);
    List& operator=(List&& rhs);

    iterator begin() 
    {
        iterator itr{*this, head};
        return ++itr;
    }
    const iterator begin() const 
    {
        const_iterator itr{*this, head};
        return head->next;
    }
    iterator end() 
    {
        iterator itr{*this, tail};
        return itr;
    }
    const iterator end() const 
    {
        const_iterator itr{*this, tail};
        return itr;
    }

    iterator insert(iterator itr, const T& x);
    iterator insert(iterator itr, T&& x);

    iterator erase(iterator itr);
    iterator erase(iterator from, iterator to);

    int size() const {return theSize;}
    bool empty() const {return theSize == 0;}

    void clear()
    {
        while (!empty())
            pop_front();
    }

    T& front() 
    {return *begin();}
    
    const T& front() const 
    {return *begin();}
    
    T& back()
    {return *--end();}
    
    const T& back() const 
    {return *--end();}
    
    void push_front(const T& x)
    { insert(begin(),x);}

    void push_front(T&& x)
    { insert(begin(),std::move(x));}

    void push_back(const T& x)
    { insert(end(),x);}

    void push_back(T&& x)
    { insert(end(),std::move(x));}
    
    void pop_front()
    { erase(begin());}    
    
    void pop_back()
    { erase(--end());}

};

class IteratorOutOfBoundsException:public std::exception
{};

class IteratorMismatchException:public std::exception
{};

template<typename T>
struct List<T>::Node
{
    T data;
    Node* prev;
    Node* next;

    Node(const T& d=T{}, Node* p = nullptr, Node* n = nullptr): //拷贝构造函数
        data{d}, prev{p}, next{n} {}
    Node(T&& d, Node* p=nullptr, Node* n=nullptr):      //移动构造函数
        data{std::move(d)}, prev{p}, next{n} {}
};

template<typename T>
class List<T>::const_iterator
{
protected:
    const List<T>* theList; //用来指示该iterator所在的List
    Node* current;      //iterator的数据只有一个指向当前Node的指针

    T& retrieve() const {return current->data;}
    
    const_iterator(const List<T>& lst, Node *p):
    theList{&lst}, current{p} {}  //这实际上就是个隐性类型转化的函数（虽然是个构造函数）
    
    friend class List<T>;

public:
    const_iterator(): current{nullptr} {}
    const T& operator*() const
    {return retrieve();}

    const_iterator& operator++()    //重载前置递增运算符，引用是为了减少内存使用和为了可以连续使用递增运算符
    {
        current = current -> next;
        return *this;
    }
    const_iterator operator++(int)     //重置后置递增运算符
    {
        const_iterator old = *this;
        ++(*this);
        return old;
    }
    bool operator==(const const_iterator& rhs) const
    { return current == rhs.current;}
    bool operator!=(const const_iterator& rhs) const
    { return !(current==rhs.current);}

    void assertIsValid() const
    {
        if(theList == nullptr || current == nullptr || current==theList->head)
            throw IteratorOutOfBoundsException{};
    }
};

template<typename T>
class List<T>::iterator:public const_iterator
{
protected:
    iterator(Node* p):const_iterator{p} {}
    friend class List<T>;

public:
    iterator() {}
    T& operator*()
    {return const_iterator::retrieve();}
    const T& operator*() const
    {return const_iterator::retrieve();}
    
    iterator& operator++()
    {
        this->current = this->current->next;
        return *this;
    }
    iterator operator++(int)
    {
        iterator old = *this;
        ++(*this);
        return old;
    }
};

template<typename T>
void List<T>::init()        //创建一个空的，只包含头节点和尾节点的List
{
    theSize = 0;
    head = new Node;
    tail = new Node;
    head->next = tail;
    tail->prev = head;
}

template<typename T>
List<T>::List()
{init();}

template<typename T>
List<T>::List(const List& rhs)
{
    init();
    for(auto& x : rhs)
        push_back(x);
}

template<typename T>
List<T>::List(List&& rhs):theSize{rhs.theSize}, head{rhs.head}, tail{rhs.tail}
{
    rhs.theSize = 0;
    rhs.head = nullptr;
    rhs.tail = nullptr;
}

template<typename T>
List<T>& List<T>::operator=(const List& rhs)
{
    List copy = rhs;
    std::swap(*this, copy);
    return *this;
}

template<typename T>
List<T>& List<T>::operator=(List&& rhs)
{
    std::swap(theSize, rhs.theSize);
    std::swap(head, rhs.head);
    std::swap(tail, rhs.tail);
    return *this;
}

template<typename T>
List<T>::~List()
{
    clear();
    delete head;
    delete tail;
}

template<typename T>
typename List<T>::iterator List<T>::insert(iterator itr, const T& x)
{
    itr.assertIsValid();
    if (itr.theList!=this)
        throw IteratorMismatchException{};
    
    Node* p = itr.current;
    ++theSize;
    return {p->prev = p->prev->next = new Node{x,p->prev,p}};
}

template<typename T>
typename List<T>::iterator List<T>::insert(iterator itr, T&& x)
{
    itr.assertIsValid();
    if (itr.theList!=this)
        throw IteratorMismatchException{};

    Node* p = itr.current;
    ++theSize;
    return {p->prev = p->prev->next = new Node{std::move(x), p->prev, p}};
}

template<typename T>
typename List<T>::iterator List<T>::erase(iterator itr)
{
    Node* p = itr.current;
    iterator retVal{p->next};
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
    --theSize;
    
    return retVal;      //返回的是被删除节点的下一个
}

template<typename T>
typename List<T>::iterator List<T>::erase(iterator from, iterator to)
{
    for(auto itr = from; itr!=to;)
        itr=erase(itr);     //由于erase(iterator)的特性，itr会自动递增
    return to;
}

#endif