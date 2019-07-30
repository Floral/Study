#ifndef PRAC7_4
#define PRAC7_4
#include<string>
#include<iostream>

using std::string;

struct Person
{
    Person() = default;
    Person(string s):name(s){}
    Person(string s0,string s1):name(s0),address(s1){}

    string getName() const {return name;}
    string getAddress() const {return address;}
    string name;
    string address;
};

std::istream& read(std::istream is,Person p)
{
    is>>p.name>>p.address;
    return is;
}
std::ostream& print(std::ostream os,const Person p)
{
    os<<p.getName()<<" "<<p.getAddress();
    return os;
}

#endif