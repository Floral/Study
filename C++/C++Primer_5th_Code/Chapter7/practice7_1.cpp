#include<iostream>
#include<string>


using std::cin; using std::cout; using std::endl;
using std::string;

struct Sales_data
{
    std::string bookNo;
    unsigned units_sold=0;
    double revenue=0.0;
};


int main()
{
    Sales_data total;
    if (cin>>total.bookNo>>total.units_sold>>total.revenue)
    {
        Sales_data trans;
        while (cin>>trans.bookNo>>total.units_sold>>trans.revenue)
        {
            if (total.bookNo == trans.bookNo)
            {
                total.units_sold+=trans.units_sold;
                total.revenue+=trans.revenue;
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