#ifndef TEXTQUERY
#define TEXTQUERY

#include<iostream>
#include<fstream>
#include<memory>
#include<string>
#include<vector>
#include<map>
#include<set>
#include"StrVec.h"

class QueryResult;

class TextQuery
{
public:
    TextQuery(){};
    TextQuery(std::ifstream&);

    QueryResult query(const std::string);

private:
    std::shared_ptr<StrVec> data;
    std::map<std::string, std::shared_ptr<std::set<size_t>>> word_map;
    std::map<std::string, size_t> word_count;
};

class QueryResult
{
    friend std::ostream& print(std::ostream&,const QueryResult&);
public:
    QueryResult():times(0){};
    QueryResult(const std::string,
                std::shared_ptr<StrVec>,
                std::shared_ptr<std::set<size_t>>,
                const size_t);
    // size_t times() const;


private:
    const std::string found_word;

    const std::shared_ptr<std::set<size_t>> lines;
    const std::shared_ptr<StrVec> data;
    const size_t times;
};

std::ostream& print(std::ostream&,const QueryResult&);

#endif