#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;
void dispVector(const vector<string> &v)
{
    for (auto &i : v)
    {
        cout<<i<<" ";
    }
    cout<<endl;
}
void elimDups(vector<string> &words)
{
    sort(words.begin(),words.end());
    dispVector(words);
    auto end_unique = unique(words.begin(),words.end());
    
    cout<<"in:"<<words.size()<<endl;

    dispVector(words);
    words.erase(end_unique,words.end());
}

void biggies(vector<string> &words,vector<string>::size_type sz)
{
    elimDups(words);
    stable_sort(words.begin(),words.end(),[](const string &a,const string &b)
                                          {return a.size()<b.size();});

    auto wc = partition(words.begin(),words.end(),[sz](const string &a){return a.size()<sz;});

    auto count = count_if(words.cbegin(),words.cend(),
                          [](const string &s){return s.size()>5;});
    
    cout<<count<<" "<<(count==1?"word":"words")
    <<" of length "<<"6"<<" or longer "<<endl;

    for_each(wc,words.end(),[](const string &s){cout<<s<<" ";});
}

int main()
{
    vector<string> v;
    // vector<string>::size_type sz;
    string i;
    while (cin>>i)
    {
        v.push_back(i);
    }
    cout<<"before:"<<endl;
    dispVector(v);
    
    biggies(v,4);
    cout<<endl;
    return 0;
}