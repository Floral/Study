#include<iostream>
#include<string>
#include"practice7_2.h"

using std::cin; using std::cout; using std::endl;
using std::string;


int main()
{
    Sales_data total;
    if (cin>>total.bookNo>>total.units_sold>>total.revenue)
    {
        Sales_data trans;
        while (cin>>trans.bookNo>>total.units_sold>>trans.revenue)
        {
            if (total.isbn() == trans.isbn())
            {
                total.combine(trans);
            }
            else
            {
                cout<<total.bookNo<<" "<<total.units_sold<<" "<<total.revenue<<endl;
                total=trans;
            }
        }
        cout<<total.bookNo<<" "<<total.units_sold<<" "<<total.revenue<<endl;
    }
    else
    {
        cout<<"No data?!"<<endl;
    }
    return 0;
}