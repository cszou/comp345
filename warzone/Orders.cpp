#include <iostream>
#include<vector>
#include<string>
#include"Orders.h"

    Order::Order(){
     this->name="order";
        std::cout<<"order created..."<<std::endl;
    }
    Order::~Order(){
    }//destructor
     std::string Order:: call(){
        return 0;
     }
     void Order::execute(Order* item){};

    std::string Order:: description(){
         return "it use for";
    }//no need maybe
    
    void Order::nameaccess(std::string newname){
        this->name=newname;
    }
    Order::Order(const Order& e) {//copy consrtuctor
    name  = e.name;
}
    Order& Order::operator=(const Order& e) { //assignment operator
    name  = e.name;
    return *this;
}
    std::ostream& operator<<(std::ostream &s,  Order *i) {
    return s << i->name;//string insertion operator
}

    std::ostream& operator<<(std::ostream& s, OrderList& ol)
    {
        return s << "This is a list of orders." << std::endl;
    }
 
    Advance::Advance(){
       nameaccess("advance");
       std::cout<<"initiate advance!"<<std::endl;
    }
    Advance::~Advance(){
         std::cout<<"advance class destruction called"<<std::endl;

    }
    std::string Advance::call(){
        return "it use for advance";
    }
    void Advance::validate(Order* item){
        std::cout<<"advance order validated!"<<std::endl;
    }
    void Advance::execute(Order* item){
        validate(item);
        std::cout<<"advance order executed!"<<std::endl;
    }
    Advance::Advance(const Advance& s) : Order(s) {
}
    Advance& Advance::operator=(const Advance& s) {
    Order::operator= (s);
    return *this;
}

    Deploy::Deploy(){
       nameaccess("deploy");
       std::cout<<"initiate deploy!"<<std::endl;
    }
    Deploy::~Deploy(){
      std::cout<<"deploy class destruction called"<<std::endl;

    }
    std::string Deploy::call(){
        return "it use for deploy";
    }

    void Deploy::validate(Order* item){
        std::cout<<"deploy order validated!"<<std::endl;
    }
    void Deploy::execute(Order* item){
        validate(item);
        std::cout<<"deploy order executed!"<<std::endl;
    }
    Deploy::Deploy(const Deploy& s) : Order(s) {
}   
    Deploy& Deploy::operator=(const Deploy& s) {
  Order::operator= (s);
  return *this;
}

    Bomb::Bomb(){
       nameaccess("bomb");
       std::cout<<"initiate bomb!"<<std::endl;
    }
    Bomb::~Bomb(){
       std::cout<<"bomb class destruction called"<<std::endl;
    }
    std::string Bomb::call(){
        return "it use for bomb";
    }
    void Bomb::validate(Order* item){
        std::cout<<"bomb order validated!"<<std::endl;
    }
    void Bomb::execute(Order* item){
        validate(item);
        std::cout<<"bomb order executed!"<<std::endl;
    }
    Bomb::Bomb(const Bomb& s) : Order(s) {
}
    Bomb& Bomb::operator=(const Bomb& s) {
    Order::operator= (s);
    return *this;
}

    Blockade::Blockade(){
       nameaccess("blockade");
       std::cout<<"initiate blockade!"<<std::endl;
    }
    Blockade::~Blockade(){
       std::cout<<"blockade class destruction called"<<std::endl;
    }
    std::string Blockade::call(){
        return "it use for blockade";
    }
    void Blockade::validate(Order* item){
        std::cout<<"blockade order validated!"<<std::endl;
    }
    void Blockade::execute(Order* item){
        validate(item);
        std::cout<<"blockade order executed!"<<std::endl;
    }
    Blockade::Blockade(const Blockade& s) : Order(s) {
}
    Blockade& Blockade::operator=(const Blockade& s) {
    Order::operator= (s);
    return *this;
}
   
    Airlift::Airlift(){
       nameaccess("airlift");
       std::cout<<"initiate airlift!"<<std::endl;
    }
    Airlift::~Airlift(){
       std::cout<<"airlift class destruction called"<<std::endl;
    }
    std::string Airlift::call(){
        return "it use for airlift";
    }
    void Airlift::validate(Order* item){
        //validate part
        std::cout<<"airlift order validated!"<<std::endl;
    }
    void Airlift::execute(Order* item){
        validate(item);
        std::cout<<"airlift order executed!"<<std::endl;
    }
    Airlift::Airlift(const Airlift& s) : Order(s) {
    }
    Airlift& Airlift::operator=(const Airlift& s) {
    Order::operator= (s);
    return *this;
    }

    Negotiate::Negotiate(){
       nameaccess("negotiate");
       std::cout<<"initiate negotiate!"<<std::endl;
    }
    Negotiate::~Negotiate(){
       std::cout<<"negotiate class destruction called"<<std::endl;
    }
    std::string Negotiate::call(){
        return "it use for negotiate";
    }
    void Negotiate::validate(Order* item){
        //validate part
        std::cout<<"negotiate order validated!"<<std::endl;
    }
    void Negotiate::execute(Order* item){
        validate(item);
        std::cout<<"negotiate order executed!"<<std::endl;
    }
    Negotiate::Negotiate(const Negotiate& s) : Order(s) {
}
    Negotiate& Negotiate::operator=(const Negotiate& s) {
    Order::operator= (s);
    return *this;
}

    OrderList::OrderList(){
    }
    OrderList::~OrderList(){
	std::cout << "Destroying OrdersList" << std::endl;
	for (auto order : list) {
		delete order;
		order = NULL;
	}
    std::cout <<"pointers destroyed"<< std::endl;
	list.clear();
    std::cout << "orderlist destroyed" << std::endl;
}

//copy constructor:
OrderList::OrderList(const OrderList& orderlistobj)
{
    std::cout<<"copy constructor for orderlist"<<std::endl;

 for (auto order : orderlistobj.list) {

  if (Deploy* deploy1 = dynamic_cast<Deploy*>(order)) {
   this->list.push_back(new Deploy(*deploy1));
  }
  else if (Advance* advance1 = dynamic_cast<Advance*>(order)) {
   this->list.push_back(new Advance(*advance1));
  }
  else if(Bomb* bomb1 = dynamic_cast<Bomb*>(order)) {
   this->list.push_back(new Bomb(*bomb1));
  }
  else if (Blockade* blockade1 = dynamic_cast<Blockade*>(order)) {
   this->list.push_back(new Blockade(*blockade1));
  }
  else if (Airlift* airlift1 = dynamic_cast<Airlift*>(order)) {
   this->list.push_back(new Airlift(*airlift1));
  }
  else if (Negotiate* negotiate1 = dynamic_cast<Negotiate*>(order)) {
   this->list.push_back(new Negotiate(*negotiate1));
  }
 }
}
OrderList & OrderList:: operator = (const OrderList& d){
        std::cout<<"asss constructor for orderlist"<<std::endl;

    for(int i = 0;i< d.list.size();i++){
        list.push_back(new Order(*d.list[i]));
    }
    return *this;
}



    Order* OrderList::invoke(int k){
        return list[k];
    }
    void OrderList::removal(int i){
         
        if (i>list.size())
        std::cout<<"out of order"<<std::endl;
        else{ 
           Order* k = list[i-1];
           
           list.erase(list.begin()+i-1);
           std::cout<<"the order want to cancel is : "<<k<<std::endl;
           std::cout<<"cancel part finished\n"<<std::endl;
           //<<"has been removed"<<std::endl;
        }
    }
    int OrderList::listsize(){
        return list.size();
    }
    void OrderList::move(int pos,int nextpos){//move part 
        if(nextpos>pos){
           list.insert(list.begin()+nextpos-1,list[pos-1]);
           list.erase(list.begin()+pos-1);
           std::cout<<"next bigger"<<std::endl;
        }
        else if(nextpos<pos){
           list.insert(list.begin()+nextpos-1,list[pos-1]);
           list.erase(list.begin()+pos);
           std::cout<<"next smaller"<<std::endl;
        }else
           ;
        
    };
    void OrderList::add(Order* k1){
    list.push_back(k1);
    }
 
