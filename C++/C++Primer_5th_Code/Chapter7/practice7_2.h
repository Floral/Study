#ifndef PRAC7_2
#define PRAC7_2
#include<iostream>
#include<string>
using std::string;

struct Sales_data
{
    string isbn() const {return bookNo;}
    Sales_data& combine(const Sales_data&);
    double avg_price() const;
    
    string bookNo;
    unsigned units_sold=0;
    double revenue=0.0;
};

Sales_data& Sales_data::combine(const Sales_data &rhs)
{
    units_sold+=rhs.units_sold;
    revenue+=rhs.revenue;
    return *this;
}

double Sales_data::avg_price() const
{
    if (units_sold)
        return revenue/units_sold;
    else
        return 0;
}

Sales_data add(const Sales_data&,const Sales_data&);
std::ostream &print(std::ostream&,const Sales_data&);
std::istream &read(std::istream&,Sales_data&);

#endif