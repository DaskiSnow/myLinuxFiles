#include "TextQuery.cc"
#include <iostream>
#include <string>
#include <memory>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ostream;
using std::shared_ptr;

class Query_base
{
friend class Query;
protected:
    virtual ~Query_base() = default;
private:
    virtual QueryResult eval(const TextQuery & tq) const = 0;
    virtual string rep() const = 0;
};

class Query
{
    friend Query operator~(const Query & q);
    friend Query operator|(const Query & lq, const Query & rq);
    friend Query operator&(const Query & lq, const Query & rq);
public:
    Query(const string & qstr); // 创建新WordQuery 

    QueryResult eval(const TextQuery & tq) const 
    {
        return _q->eval(tq);
    }

    string rep() const 
    {
        return _q->rep();
    }

private:
    Query(shared_ptr<Query_base> query)
    : _q(query)
    {}
    
    shared_ptr<Query_base> _q;
};

// Over
class WordQuery
: public Query_base
{
friend class Query;
public:
    WordQuery(const string & qstr)
    : _qstr(qstr)
    {}

    QueryResult eval(const TextQuery & tq) const
    {
        return tq.query(_qstr);
    }

    string rep() const
    {
        return _qstr;
    }

private:
    string _qstr;
};

class NotQuery
: public Query_base
{
friend Query operator~(const Query & query);
public:
    NotQuery(const Query & query)
    : _query(query)
    {}

    QueryResult eval(const TextQuery & tq) const;  // TODO
    
    string rep() const
    {
        return "~(" + _query.rep() + ")";
    }

private:
    Query _query;
};

Query operator~(const Query & query)
{
    return shared_ptr<Query_base>(new NotQuery(query)); 
}

QueryResult NotQuery::eval(const TextQuery & tq) const 
{
     
}

class BinaryQuery
: public Query_base
{
protected:
    BinaryQuery(const Query & lq, const Query & rq, string op)
    : _lq(lq)
    , _rq(rq)
    , _op(op)
    {}
    
    // 这里不定义eval(), 是因为从Query_base中继承了纯虚函数eval(), 应将该纯虚函数留给子类实现
    
    virtual string rep() const
    {
        return "(" + _lq.rep() + _op + _rq.rep() + ")";
    }

protected:
    Query _lq;
    Query _rq;
    string _op;
};

class AndQuery
: public BinaryQuery
{
friend Query operator&(const Query & lq, const Query & rq);
public:
    AndQuery(const Query & lq, const Query & rq)
    : BinaryQuery(lq, rq, "&")
    {}
    
    QueryResult eval(const TextQuery & tq) const override;

};

Query operator&(const Query & lq, const Query & rq)
{
    return shared_ptr<Query_base>(new AndQuery(lq, rq));
}

QueryResult AndQuery::eval(const TextQuery & tq) const
{

}

class OrQuery
: public BinaryQuery
{
friend Query operator|(const Query & lq, const Query & rq);
public:
    OrQuery(const Query & lq, const Query & rq)
    : BinaryQuery(lq, rq, "|")
    {}

    QueryResult eval(const TextQuery & tq) const override;

};

Query operator|(const Query & lq, const Query & rq)
{
    return shared_ptr<Query_base>(new OrQuery(lq, rq));
}

QueryResult OrQuery::eval(const TextQuery & tq) const
{
    QueryResult lqr = _lq.eval(tq);
    QueryResult rqr = _rq.eval(tq);
    set<int> lines()
}

ostream & operator<<(ostream & os, const Query & query)
{
    return os << query.rep();
}

int main(int argc, char* argv[])
{
    return 0;
}

