#include <iostream>
#include<vector>
#include<string>
#include"Orders.h"

    order::order(){
     this->name="order";
        std::cout<<"order created..."<<std::endl;
    }
    order::~order(){
    }//destructor
     std::string order:: call(){
        return 0;
     }
     void order::execute(order* item){};

    std::string order:: description(){
         return "it use for";
    }//no need maybe
    
    void order::nameaccess(std::string newname){
        this->name=newname;
    }
    order::order(const order& e) {//copy consrtuctor
    name  = e.name;
}
    order& order::operator=(const order& e) { //assignment operator
    name  = e.name;
    return *this;
}
    std::ostream& operator<<(std::ostream &s,  order *i) {
    return s << i->name;//string insertion operator
}
 
    advance::advance(){
       nameaccess("advance");
       std::cout<<"initiate advance!"<<std::endl;
    }
    advance::~advance(){
         std::cout<<"advance class destruction called"<<std::endl;

    }
    std::string advance::call(){
        return "it use for advance";
    }
    void advance::validate(order* item){
        std::cout<<"advance order validated!"<<std::endl;
    }
    void advance::execute(order* item){
        validate(item);
        std::cout<<"advance order executed!"<<std::endl;
    }
    advance::advance(const advance& s) : order(s) {
}
    advance& advance::operator=(const advance& s) {
    order::operator= (s);
    return *this;
}

    deploy::deploy(){
       nameaccess("deploy");
       std::cout<<"initiate deploy!"<<std::endl;
    }
    deploy::~deploy(){
      std::cout<<"deploy class destruction called"<<std::endl;

    }
    std::string deploy::call(){
        return "it use for deploy";
    }

    void deploy::validate(order* item){
        std::cout<<"deploy order validated!"<<std::endl;
    }
    void deploy::execute(order* item){
        validate(item);
        std::cout<<"deploy order executed!"<<std::endl;
    }
    deploy::deploy(const deploy& s) : order(s) {
}   
    deploy& deploy::operator=(const deploy& s) {
  order::operator= (s);
  return *this;
}

    bomb::bomb(){
       nameaccess("bomb");
       std::cout<<"initiate bomb!"<<std::endl;
    }
    bomb::~bomb(){
       std::cout<<"bomb class destruction called"<<std::endl;
    }
    std::string bomb::call(){
        return "it use for bomb";
    }
    void bomb::validate(order* item){
        std::cout<<"bomb order validated!"<<std::endl;
    }
    void bomb::execute(order* item){
        validate(item);
        std::cout<<"bomb order executed!"<<std::endl;
    }
    bomb::bomb(const bomb& s) : order(s) {
}
    bomb& bomb::operator=(const bomb& s) {
    order::operator= (s);
    return *this;
}

    blockade::blockade(){
       nameaccess("blockade");
       std::cout<<"initiate blockade!"<<std::endl;
    }
    blockade::~blockade(){
       std::cout<<"blockade class destruction called"<<std::endl;
    }
    std::string blockade::call(){
        return "it use for blockade";
    }
    void blockade::validate(order* item){
        std::cout<<"blockade order validated!"<<std::endl;
    }
    void blockade::execute(order* item){
        validate(item);
        std::cout<<"blockade order executed!"<<std::endl;
    }
    blockade::blockade(const blockade& s) : order(s) {
}
    blockade& blockade::operator=(const blockade& s) {
    order::operator= (s);
    return *this;
}
   
    airlift::airlift(){
       nameaccess("airlift");
       std::cout<<"initiate airlift!"<<std::endl;
    }
    airlift::~airlift(){
       std::cout<<"airlift class destruction called"<<std::endl;
    }
    std::string airlift::call(){
        return "it use for airlift";
    }
    void airlift::validate(order* item){
        //validate part
        std::cout<<"airlift order validated!"<<std::endl;
    }
    void airlift::execute(order* item){
        validate(item);
        std::cout<<"airlift order executed!"<<std::endl;
    }
    airlift::airlift(const airlift& s) : order(s) {
    }
    airlift& airlift::operator=(const airlift& s) {
    order::operator= (s);
    return *this;
    }

    negotiate::negotiate(){
       nameaccess("negotiate");
       std::cout<<"initiate negotiate!"<<std::endl;
    }
    negotiate::~negotiate(){
       std::cout<<"negotiate class destruction called"<<std::endl;
    }
    std::string negotiate::call(){
        return "it use for negotiate";
    }
    void negotiate::validate(order* item){
        //validate part
        std::cout<<"negotiate order validated!"<<std::endl;
    }
    void negotiate::execute(order* item){
        validate(item);
        std::cout<<"negotiate order executed!"<<std::endl;
    }
    negotiate::negotiate(const negotiate& s) : order(s) {
}
    negotiate& negotiate::operator=(const negotiate& s) {
    order::operator= (s);
    return *this;
}

    orderlist::orderlist(){
    }
    orderlist::~orderlist(){
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
orderlist::orderlist(const orderlist& orderlistobj)
{
 for (auto order : orderlistobj.list) {
std::cout<<"copy constructor for orderlist"<<std::endl;

  if (deploy* deploy1 = dynamic_cast<deploy*>(order)) {
   this->list.push_back(new deploy(*deploy1));
  }
  else if (advance* advance1 = dynamic_cast<advance*>(order)) {
   this->list.push_back(new advance(*advance1));
  }
  else if(bomb* bomb1 = dynamic_cast<bomb*>(order)) {
   this->list.push_back(new bomb(*bomb1));
  }
  else if (blockade* blockade1 = dynamic_cast<blockade*>(order)) {
   this->list.push_back(new blockade(*blockade1));
  }
  else if (airlift* airlift1 = dynamic_cast<airlift*>(order)) {
   this->list.push_back(new airlift(*airlift1));
  }
  else if (negotiate* negotiate1 = dynamic_cast<negotiate*>(order)) {
   this->list.push_back(new negotiate(*negotiate1));
  }
 }
}

//assignment operator
orderlist& orderlist::operator=(const orderlist& e) {
std::cout<<"assignment operator for orderlist "<<std::endl;
for (auto order : e.list) {
  if (deploy* deploy1 = dynamic_cast<deploy*>(order)) {
   this->list.push_back(new deploy(*deploy1));
  }
  else if (advance* advance1 = dynamic_cast<advance*>(order)) {
   this->list.push_back(new advance(*advance1));
  }
  else if(bomb* bomb1 = dynamic_cast<bomb*>(order)) {
   this->list.push_back(new bomb(*bomb1));
  }
  else if (blockade* blockade1 = dynamic_cast<blockade*>(order)) {
   this->list.push_back(new blockade(*blockade1));
  }
  else if (airlift* airlift1 = dynamic_cast<airlift*>(order)) {
   this->list.push_back(new airlift(*airlift1));
  }
  else if (negotiate* negotiate1 = dynamic_cast<negotiate*>(order)) {
   this->list.push_back(new negotiate(*negotiate1));
  }
 }
  return *this;
}

    order* orderlist::invoke(int k){
        return list[k];
    }
    void orderlist::removal(int i){
         
        if (i>list.size())
        std::cout<<"out of order"<<std::endl;
        else{ 
           order* k = list[i-1];
           
           list.erase(list.begin()+i-1);
           std::cout<<"the order want to cancel is : "<<k<<std::endl;
           std::cout<<"cancel part finished\n"<<std::endl;
           //<<"has been removed"<<std::endl;
        }
    }
    int orderlist::listsize(){
        return list.size();
    }
    void orderlist::move(int pos,int nextpos){//move part 
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
    void orderlist::add(order* k1){
    list.push_back(k1);
    }
 
