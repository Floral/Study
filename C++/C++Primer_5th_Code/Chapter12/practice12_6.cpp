#include<iostream>
#include<vector>
#include<new>

using namespace std;

vector<int>* create_vector()
{
    return new vector<int>();
}

void read_data(vector<int> *pv)
{
    int i;
    while (cin>>i)
    {
        pv->push_back(i);
    }
}

void print_vector(vector<int> *pv)
{
    for (auto i = pv->cbegin(); i != pv->cend(); ++i)
    {
        cout<<(*i)<<" ";
    }
    cout<<endl;
}

int main()
{
    vector<int> *pv = create_vector();
    read_data(pv);
    print_vector(pv);

    delete pv;

    return 0;
}