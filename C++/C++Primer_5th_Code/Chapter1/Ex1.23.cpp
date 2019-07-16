#include<iostream>
#include"Sales_item.h"

int main()
{
    Sales_item currItem,preItem;
    int cnt=0;

    if (std::cin>>preItem)
    {
        cnt=1;

        while (std::cin>>currItem)
        {
            if (currItem.isbn()==preItem.isbn())
            {
                cnt++;
            }else
            {
                std::cout<< preItem.isbn()<<" occurs "
                    <<cnt<<" times "<<std::endl;
                preItem=currItem;
                cnt=1;
            }
        }
        std::cout<<preItem.isbn()<<" occurs "
            <<cnt<<" times "<< std::endl;
    }
    
    return 0;
}