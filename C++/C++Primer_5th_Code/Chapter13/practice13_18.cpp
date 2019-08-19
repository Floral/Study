#include<iostream>
#include<vector>
#include<string>

using namespace std;

class Employee{
public:
    Employee(){}
    Employee(string name):name(name),id(++create_id){};

    size_t getID(){return id;}
    string& getName(){return name;}
private:
    string name;
    size_t id;
    static size_t create_id;
};

size_t Employee::create_id = 0;

int main()
{
    Employee e1("lqw");
    Employee e2("xhy");

    cout<<e1.getName()<<" "<<e1.getID()<<endl;    
    cout<<e2.getName()<<" "<<e2.getID()<<endl;    

    return 0;
}