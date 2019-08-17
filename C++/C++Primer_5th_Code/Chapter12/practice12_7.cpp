#include<iostream>
#include<memory>
#include<vector>

using namespace std;

shared_ptr<vector<int>> create_vector()
{
    return make_shared<vector<int>>();
}

void read_data(shared_ptr<vector<int>> pv)
{
    int i;
    while (cin>>i)
    {
        pv->push_back(i);
    }
}

void print_vector(shared_ptr<vector<int>> pv)
{
    for (auto i = pv->cbegin(); i != pv->cend(); ++i)
    {
        cout<<(*i)<<" ";
    }
    cout<<endl;
}

int main()
{
    shared_ptr<vector<int>> pv = create_vector();
    read_data(pv);
    print_vector(pv);

    return 0;
}