#pragma once

#include <iostream>
#include<vector>
#include<string>
//using namespace std;
class Order {
    
    private:
    std::string name;
    public:
    Order();
    virtual ~Order();
    virtual std::string call();
    std::string description();
    virtual void execute(Order* item);
    void nameaccess(std::string newname);
    Order(const Order& e);
    Order& operator=(const Order& e);
    friend std::ostream& operator<<(std::ostream &s,  Order *i) ;
};
     
class Advance : public Order{
    public:
    Advance();
    ~Advance();
    std::string call();
    void validate(Order* item);
    void execute(Order* item);
    Advance(const Advance& s);
    Advance& operator=(const Advance& s);

};

class Deploy : public Order{
    public:
    Deploy();
    ~Deploy();
    std::string call();
    void validate(Order* item);
    void execute(Order* item);
    Deploy(const Deploy& s);
    Deploy& operator=(const Deploy& s);
};

class Bomb : public Order{
    public:
    Bomb();
    ~Bomb();
    std::string call();
    void validate(Order* item);
    void execute(Order* item);
    Bomb(const Bomb& s);
    Bomb& /*bomb::*/operator=(const Bomb& s);
};

class Blockade : public Order{
    public:
    Blockade();
    ~Blockade();
    std::string call();
    void validate(Order* item);
    void execute(Order* item);
    Blockade(const Blockade& s);
    Blockade& operator=(const Blockade& s);
};

class Airlift : public Order{
    public:
    Airlift();
    ~Airlift();
    std::string call();
    void validate(Order* item);
    void execute(Order* item);
    Airlift(const Airlift& s);
    Airlift& operator=(const Airlift& s);
};

class Negotiate : public Order{
    public:
    Negotiate();
    ~Negotiate();
    std::string call();
    void validate(Order* item);
    void execute(Order* item);
    Negotiate(const Negotiate& s);
    Negotiate& operator=(const Negotiate& s);
};
class OrderList{
    private:
        std::vector<Order*>list;//list of order of pointer
    public:
    OrderList();
    ~OrderList();
    Order* invoke(int k);
    void removal(int i);
    int listsize();
    void move(int pos,int nextpos);
    void add(Order* k1);
    OrderList(const OrderList& orderlistobj);
    OrderList &  operator = (const OrderList& d);
    friend std::ostream& operator<<(std::ostream& s, OrderList& ol);
};
