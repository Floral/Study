#include<iostream>
#include<iterator>
#include<vector>
#include<string>
#include<algorithm>
#include<numeric>
using namespace std;

int main()
{
    istream_iterator<int> in(cin),eof;
    ostream_iterator<int> out(cout," ");

    // cout<< accumulate(in,eof,0)<<endl;
    vector<int> v(in,eof);

    copy(v.cbegin(),v.cend(),out);
    cout<<endl;
    return 0;
}