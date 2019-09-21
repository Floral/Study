#ifndef QUERY_BASE
#define QUERY_BASE

#include"TextQuery.h"
#include<memory>
#include<set>

class Query;

class Query_base{
    friend class Query;
protected:
    using line_no = TextQuery::line_no;
    virtual ~Query_base() = default;

private:
    virtual QueryResult eval(const  TextQuery&) const = 0;

    virtual std::string rep() const = 0;
};

class WordQuery:public Query_base{
    friend class Query;

    WordQuery(const std::string &s):query_word(s) {}
    QueryResult eval(const TextQuery &t) const
                { return t.query(query_word); }

    std::string rep() const { return query_word; }
    std::string query_word;
};


class NotQuery:public Query_base{
    friend Query operator~(const Query &);

    NotQuery(const Query &q):query(q) {}
    std::string rep() const { return "~("+query.rep()+")";}
    QueryResult eval(const TextQuery&) const;
    Query query;
};

inline
Query operator~(const Query &operand)
{
    return std::make_shared<Query_base>(new NotQuery(operand));
}

class BinaryQuery:public Query_base{
        friend Query operator&(const Query&, const Query&);
protected:
    BinaryQuery(const Query &l, const Query &r, std::string s):
                lhs(l), rhs(r), opSym(s) {}
    
    std::string rep() const {return "("+lhs.rep()+" "
                                    + opSym + " "
                                    + rhs.rep() + " ";}

    Query lhs,rhs;
    std::string opSym;
};

class AndQuery: public BinaryQuery{
    friend Query operator&(const Query&, const Query&);

    AndQuery(const Query &left, const Query &right):
            BinaryQuery(left, right, "&") {}

    QueryResult eval(const TextQuery&) const;
};

inline
Query operator&(const Query &lhs,const Query &rhs)
{
    return std::shared_ptr<Query_base>(new AndQuery(lhs,rhs));
}

class OrQuery: public BinaryQuery{
    friend Query operator|(const Query&, const Query&);

    OrQuery(const Query &left, const Query &right):
            BinaryQuery(left, right, "|") {}

    QueryResult eval(const TextQuery&) const;
};

inline
Query operator|(const Query &lhs,const Query &rhs)
{
    return std::shared_ptr<Query_base>(new OrQuery(lhs,rhs));
}

QueryResult
OrQuery::eval(const TextQuery& text) const
{
    auto right = rhs.eval(text), left = lhs.eval(text);

    auto ret_lines =
        std::make_shared<std::set<line_no>>(left.begin(),left.end());
    ret_lines->insert(right.begin(), right.end());
    
    return QueryResult(rep(),ret_lines,left.get_file());
}

#endif