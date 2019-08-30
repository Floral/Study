#include<iostream>
#include<string>
#include"practice15_5.h"

using namespace std;

int main()
{
    Quote q("abcdefg",12.3);
    Bulk_quote bq("abcdefg",12.3,3,0.1);

    print_total(cout, bq, 4);
    return 0;
}