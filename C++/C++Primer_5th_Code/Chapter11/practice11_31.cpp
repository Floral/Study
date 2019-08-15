#include<iostream>
#include<map>
#include<string>

using namespace std;

int main()
{
    multimap<string, string> authors;

    authors.insert({"hxd","asd1"});
    authors.insert({"hxd","asd2"});

    authors.insert({"lx","qwe"});
    
    authors.insert({"xhy","hhh"});
    authors.insert({"lqw","test1"});
    authors.insert({"lqw","test2"});
    authors.insert({"lqw","test3"});

    auto iter = authors.find("lqw");
    auto count = authors.count("lqw");

    string book("test2");
    while (count)
    {
        if (iter->second==book)
        {
            authors.erase(iter);
            break;
        }
        else
        {
            iter++;
        }
        count--;
    }
    
    for (const auto &i : authors)
    {
        cout<<i.first<<" "<<i.second<<endl;
    }
    
    return 0;
}