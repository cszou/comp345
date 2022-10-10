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
    Order(const Order& e);//copy constructor
    Order& operator=(const Order& e);//assignment operator
    friend std::ostream& operator<<(std::ostream &s,  Order *i) ;//stream insertion operator
};
     
class Advance : public Order{
    public:
    Advance();
    ~Advance();
    std::string call();
    void validate(Order* item);
    void execute(Order* item);
    Advance(const Advance& s);//copy constructor
    Advance& operator=(const Advance& s);//assignment operator
    friend std::ostream& operator<<(std::ostream &s,  Advance *i) ;//stream insertion operator
};

class Deploy : public Order{
    public:
    Deploy();
    ~Deploy();
    std::string call();
    void validate(Order* item);
    void execute(Order* item);
    Deploy(const Deploy& s);//copy constructor
    Deploy& operator=(const Deploy& s);//assignment operator
    friend std::ostream& operator<<(std::ostream &s,  Deploy *i) ;//stream insertion operator
};

class Bomb : public Order{
    public:
    Bomb();
    ~Bomb();
    std::string call();
    void validate(Order* item);
    void execute(Order* item);
    Bomb(const Bomb& s);//copy constructor
    Bomb& operator=(const Bomb& s);//assignment operator
    friend std::ostream& operator<<(std::ostream &s,  Bomb *i) ;//stream insertion operator
};

class Blockade : public Order{
    public:
    Blockade();
    ~Blockade();
    std::string call();
    void validate(Order* item);
    void execute(Order* item);
    Blockade(const Blockade& s);//copy constructor
    Blockade& operator=(const Blockade& s);//assignment operator
    friend std::ostream& operator<<(std::ostream &s,  Blockade *i) ;//stream insertion operator
};

class Airlift : public Order{
    public:
    Airlift();
    ~Airlift();
    std::string call();
    void validate(Order* item);
    void execute(Order* item);
    Airlift(const Airlift& s);//copy constructor
    Airlift& operator=(const Airlift& s);//assignment operator
    friend std::ostream& operator<<(std::ostream &s,  Airlift *i) ;//stream insertion operator

};

class Negotiate : public Order{
    public:
    Negotiate();
    ~Negotiate();
    std::string call();
    void validate(Order* item);
    void execute(Order* item);
    Negotiate(const Negotiate& s);//copy constructor
    Negotiate& operator=(const Negotiate& s);//assignment operator
    friend std::ostream& operator<<(std::ostream &s,  Negotiate *i) ;//stream insertion operator

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
    OrderList(const OrderList& orderlistobj);//copy constructor
    OrderList &  operator = (const OrderList& d);//assignment operator
    friend std::ostream& operator<<(std::ostream& s, OrderList& ol);//stream insertion operator
};