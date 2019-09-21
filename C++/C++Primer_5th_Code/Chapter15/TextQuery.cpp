#include<iostream>
#include<fstream>
#include<sstream>
#include<memory>
#include<vector>
#include<string>
#include<cctype>
#include<map>
#include<algorithm>
#include"TextQuery.h"

using std::string; using std::ifstream; 
using std::istringstream; using std::vector;
using std::set; using std::map; using std::shared_ptr;
using std::ostream;
using std::make_shared; using std::make_shared;

TextQuery::TextQuery(ifstream& infile):data(new vector<string>)
{
    string line;
    size_t line_no = 1;
    size_t times = 0;
    while (getline(infile,line))
    {
        data->push_back(line);      // push each line into the vector
        istringstream iss(line);
        string word;
        while (iss>>word)
        {
            word.erase(std::remove_if(word.begin(),word.end(),ispunct),word.end());
            if (word_map.count(word)==0)
            {
                word_map[word].reset(new set<size_t>());
                word_count[word] = 0;
            }
            
            word_map[word]->insert(line_no);              // build a word to lines map
            word_count[word]++;
        }
        line_no++;
    }
}

QueryResult TextQuery::query(const string target) const
{
    auto it = word_map.find(target);
    auto it2 = word_count.find(target);
    if (it!=word_map.end())
    {
        QueryResult ret(target,data,it->second,it2->second);
        return ret;
    }
    else/* condition */
    {
        QueryResult ret(target,nullptr,nullptr,0);
        return ret;
    }
}

QueryResult::QueryResult(const string found_word,
                shared_ptr<set<size_t>> lines,
                shared_ptr<vector<string>> data):found_word(found_word),data(data),lines(lines){};

ostream& print(ostream& os,const QueryResult &result)
{
    os<<result.found_word<<" occurs "
    <<result.times<<(result.times>1 ? " times":" time")<<std::endl;
    
    if (result.times==0)
        return os;

    auto it = result.lines->cbegin();
    while (it != result.lines->cend())
    {
        os<<"(line "<<(*it)<<") ";
        os<<(*result.data)[*it-1]<<std::endl;
        it++;
    }
    return os;
}