#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<algorithm>
#include<iterator>

using namespace std;
int main()
{
    ifstream in("data.in");
    istream_iterator<string> str_it(in),eof;
    vector<string> vec;
    back_insert_iterator<vector<string>> vt = back_inserter(vec);

    while (str_it!=eof)
    {
        vt=*(str_it++);
    }
    
    copy(vec.cbegin(),vec.cend(),ostream_iterator<string>(cout," "));
    cout<<endl;
    return 0;
}