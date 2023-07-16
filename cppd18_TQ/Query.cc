#include "TextQuery.hh"
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

Query::Query(const string & qstr)
: _q(shared_ptr<Query_base>(new WordQuery(qstr)))
{}

class NotQuery
: public Query_base
{
friend Query operator~(const Query & query);
public:
    NotQuery(const Query & query)
    : _q(query)
    {}

    QueryResult eval(const TextQuery & tq) const;  
    
    string rep() const
    {
        return "~(" + _q.rep() + ")";
    }

private:
    Query _q;
};

Query operator~(const Query & query)
{
    return shared_ptr<Query_base>(new NotQuery(query)); 
}

QueryResult NotQuery::eval(const TextQuery & tq) const 
{
     QueryResult qr = _q.eval(tq);
     set<int> lines;
     for(unsigned long i = 0; i < qr._pFile->size(); ++i)
     {
         if(qr._lines.count(i) == 0)
         {
             lines.insert(i);
         }
     }
     string qstr = rep();
     int freq = lines.size();
     return QueryResult(qstr, freq, lines, qr._pFile);
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
        return "(" + _lq.rep() + " " + _op + " " + _rq.rep() + ")";
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
    QueryResult lqr = _lq.eval(tq);
    QueryResult rqr = _rq.eval(tq);
    set<int> lines;
    for(auto & line : lqr._lines)
    {
        if(rqr._lines.count(line) > 0)
        {
            lines.insert(line);
        }
    }
    string qstr = rep();
    int freq = lines.size();
    return QueryResult(qstr, freq, lines, lqr._pFile); 
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
    set<int> lines(lqr._lines.begin(), lqr._lines.end());
    lines.insert(rqr._lines.begin(), rqr._lines.end());
    string qstr = rep();
    int freq = lines.size();
    return QueryResult(qstr, freq, lines, lqr._pFile);
}

ostream & operator<<(ostream & os, const Query & q)
{
    return os << q.rep();
}

std::ostream & operator<<(std::ostream & os, QueryResult qr)
{
    os << "Executing Query for: " << qr._qstr << "\n" 
       << qr._qstr << " occurs " << qr._freq << (qr._freq > 1 ? " times" : " time") << "\n";
    for(const auto & lineIdx : qr._lines)
    {
        os << "(line "<< lineIdx + 1 << ") " << (*qr._pFile)[lineIdx] + "\n"; 
    }
    return os;
}

int main(int argc, char* argv[])
{
    ifstream ifs("The_Holy_Bible.txt");
    TextQuery tq(ifs);
    Query q = Query("i") & Query("excellent") & ~Query("fail");
    QueryResult qr = q.eval(tq);
    cout << qr << endl;
    return 0;
}

