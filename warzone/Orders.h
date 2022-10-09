#include <iostream>
#include<vector>
#include<string>
//using namespace std;
class order {
    
    private:
    std::string name;
    public:
    order();
    virtual ~order();
    virtual std::string call();
    std::string description();
    virtual void execute(order* item);
    void nameaccess(std::string newname);
    order(const order& e);
    order& operator=(const order& e);
    friend std::ostream& operator<<(std::ostream &s,  order *i) ;
};
     
class advance : public order{
    public:
    advance();
    ~advance();
    std::string call();
    void validate(order* item);
    void execute(order* item);
    advance(const advance& s);
    advance& operator=(const advance& s);

};

class deploy : public order{
    public:
    deploy();
    ~deploy();
    std::string call();
    void validate(order* item);
    void execute(order* item);
    deploy(const deploy& s);
    deploy& operator=(const deploy& s);
};

class bomb : public order{
    public:
    bomb();
    ~bomb();
    std::string call();
    void validate(order* item);
    void execute(order* item);
    bomb(const bomb& s);
    bomb& /*bomb::*/operator=(const bomb& s);
};

class blockade : public order{
    public:
    blockade();
    ~blockade();
    std::string call();
    void validate(order* item);
    void execute(order* item);
    blockade(const blockade& s);
    blockade& operator=(const blockade& s);
};

class airlift : public order{
    public:
    airlift();
    ~airlift();
    std::string call();
    void validate(order* item);
    void execute(order* item);
    airlift(const airlift& s);
    airlift& operator=(const airlift& s);
};

class negotiate : public order{
    public:
    negotiate();
    ~negotiate();
    std::string call();
    void validate(order* item);
    void execute(order* item);
    negotiate(const negotiate& s);
    negotiate& operator=(const negotiate& s);
};
class orderlist{
    private:
        std::vector<order*>list;//list of order of pointer
    public:
    //std::vector<order*>list;//list of order of pointer
    orderlist();
    ~orderlist();
    order* invoke(int k);
    void removal(int i);
    int listsize();
    void move(int pos,int nextpos);
    void add(order* k1);
    orderlist(const orderlist& orderlistobj);
    orderlist &  operator = (const orderlist& d);
};
