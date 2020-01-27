#ifndef LIST
#define LIST

#include<algorithm>

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

    iterator begin() {return head->next;}
    const iterator begin() const {return head->next;}
    iterator end() {return tail;}
    const iterator end() const {return tail;}

    int size() const {return theSize;}
    bool empty() const {return theSize == 0;}

    void clear();
    T& front() {return *begin();}
    const T& front() const {return *begin();}
    T& back() {return *--end();}
    const T& back() const {return *--end();}
    void push_front(const T& x);
    void push_front(T&& x);
    void push_back(const T& x);
    void push_back(T&& x);
    void pop_front();
    void pop_back();

    iterator insert(iterator itr, const T& x);
    iterator insert(iterator itr, T&& x);

    iterator erase(iterator itr);
    iterator erase(iterator from, iterator to);
};

template<typename T>
struct List<T>::Node
{
    T data;
    Node* prev;
    Node* next;

    Node(const T& d=T{}, Node* p = nullptr, Node* n = nullptr):
        data{d}, prev{p}, next{n} {}
    Node(T&& d, Node* p=nullptr, Node* n=nullptr):
        data{std::move(d)}, prev{p}, next{n} {}
};

template<typename T>
class List<T>::const_iterator
{
protected:
    Node* current;

    T& retrieve() const {return current->data;}
    const_iterator(Node *p): current{p} {}
    friend class List<T>;

public:
    const_iterator(): current{nullptr} {}
};

template<typename T>
class List<T>::iterator:public const_iterator
{

};

template<typename T>
List<T>::List()
{
}
template<typename T>
List<T>::~List()
{
}


#endif