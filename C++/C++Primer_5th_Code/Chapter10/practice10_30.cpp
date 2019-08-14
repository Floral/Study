#include<iostream>
#include<iterator>
#include<algorithm>
#include<vector>

using namespace std;

int main()
{
    istream_iterator<int> int_it(cin),eof;
    ostream_iterator<int> int_ot(cout," ");

    vector<int> v;

    copy(int_it,eof,back_inserter(v));
    sort(v.begin(),v.end());

    copy(v.cbegin(),v.cend(),int_ot);    
    cout<<endl;
    return 0;
}