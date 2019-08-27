#include<iostream>

class A{
    friend std::ostream& operator<<(std::ostream &os,const A&);
    public:
        int operator*(){return b;}
        A* operator->(){return this;}
        int geta(){return a;}
        int getb(){return b;}
    private:
        int a=0;
        int b=1;
};
std::ostream& operator<<(std::ostream &os,const A& a)
{
    os<<a.a<<' '<<a.b;
    return os;
}
int main()
{
    A a;
    A *pa=&a;
    std::cout<<*a<<','<<*a<<std::endl;
    std::cout<<*pa<<','<<*pa<<std::endl;
    std::cout<<a->geta()<<','<<a->getb()<<std::endl;
    return 0;
}