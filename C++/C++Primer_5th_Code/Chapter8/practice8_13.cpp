#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>

using namespace::std;

struct PersonInfo
{
    /* data */
    string name;
    vector<string> phones;
};

int main()
{
    string line,word;
    vector<PersonInfo> people;
    fstream fs("chinese-3500.txt");

    while (getline(fs,line))
    {
        /* code */
        stringstream ss(line);
        PersonInfo info;
        ss >> info.name;
        while (ss>>word)
        {
            /* code */
            info.phones.push_back(word);
        }
        people.push_back(info);
    }
    for (auto &i : people)
    {
        std::cout<<i.name+" ";
        ostringstream oss;
        
        for (auto &j : i.phones)
        {
            oss<<j+" ";
        }
        oss<<endl;
        cout<<oss.str();
    }
    
    return 0;
}