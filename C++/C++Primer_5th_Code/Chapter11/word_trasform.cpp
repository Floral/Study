#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<map>
#include<string>

using namespace std;

void word_transform(ifstream &, ifstream &);
map<string, string> buildMap(ifstream &);
const string& transform(const string&,const map<string, string>&);

int main()
{

    return 0;
}

void word_transform(ifstream &map_file, ifstream &input)
{
    auto trans_map = buildMap(map_file);
    string text;
    while (getline(input, text))
    {
        istringstream stream(text);
        string word;
        bool firstword = true;
        while (stream >> word)
        {
            if (firstword)
            {
                firstword = false;
            }
            else
            {
                cout<<" ";
            }
            cout<<transform(word, trans_map);
        }
        cout<<endl;
    }
}

map<string, string> buildMap(ifstream &map_file)
{
    map<string, string> trans_map;
    string key;
    string value;
    while (map_file >> key && getline(map_file, value))
    {
        if(value.size()>1)
            trans_map[key] = value.substr(1);
        else
            throw runtime_error("no rule for "+key);
    }
    return trans_map;
}

const string& transform(const string &s,const map<string, string> &m)
{
    auto map_it=m.find(s);
    if (map_it!=m.cend())
    {
        return map_it->second;
    }
    else
    {
        return s;
    }
    
}