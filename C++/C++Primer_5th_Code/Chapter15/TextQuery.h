#ifndef TEXTQUERY
#define TEXTQUERY

#include<iostream>
#include<fstream>
#include<memory>
#include<string>
#include<vector>
#include<map>
#include<set>

class QueryResult;

class TextQuery
{
public:
    using line_no = std::vector<std::string>::size_type;
    TextQuery(){};
    TextQuery(std::ifstream&);

    QueryResult query(const std::string) const;

private:
    std::shared_ptr<std::vector<std::string>> data;
    std::map<std::string, std::shared_ptr<std::set<size_t>>> word_map;
    std::map<std::string, size_t> word_count;
};

class QueryResult
{
    friend std::ostream& print(std::ostream&,const QueryResult&);
public:
    QueryResult(){};
    QueryResult(const std::string,
                std::shared_ptr<std::set<size_t>>,
                std::shared_ptr<std::vector<std::string>>);
    // size_t times() const;


private:
    const std::string found_word;

    const std::shared_ptr<std::set<size_t>> lines;
    const std::shared_ptr<std::vector<std::string>> data;
};

std::ostream& print(std::ostream&,const QueryResult&);

#endif