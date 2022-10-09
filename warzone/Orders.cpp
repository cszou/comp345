#include <iostream>
#include<vector>
#include<string>
#include<Orders.h>

    order::order(){
     this->name="order";
        std::cout<<"order created..."<<std::endl;
    }
    order::~order(){
        
    }//destructor
 //   order::virtual std::string call(){
 //        return "hello"; }
    std::string order:: description(){
         return "it use for";
    }//no need maybe
    //virtual void execute(order* item){
       //virtual function
 //   }//used for overloading
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
};
 
    advance::advance(){
       nameaccess("advance");
       std::cout<<"initiate advance!"<<std::endl;
    }
    advance::~advance(){
        
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
    orderlist::~orderlist()
    {
	std::cout << "Destroying OrdersList" << std::endl;
	for (auto order : list) {
		delete order;
		order = NULL;
	}
    std::cout <<"pointers destroyed"<< std::endl;
	list.clear();
    std::cout << "orderlist destroyed" << std::endl;
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
           std::cout<<"next smaller";
        }else
           ;
        
    };
    void orderlist::add(order* k1){
    list.push_back(k1);
    }
 
int main()
{
    bool check = true;
    int orderfind;
    orderlist* k= new orderlist();
    while(check){
    std::cout<<"which order you want to create? 1.advance;2.deploy;3.bomb;4.blockade;5.airlift;6.negotiate;7.non"<<std::endl;
    std::cin>>orderfind;//order *o1=new order();
    switch(orderfind){
        case 1:
               { 
                advance* jd=new advance();
                jd->validate(jd);
                k->add(jd);
                break;
               }
        case 2:
               { 
                deploy* jd=new deploy();
                jd->validate(jd);
                k->add(jd);
                break;
               }
        case 3:
               { 
                bomb* jd=new bomb();
                jd->validate(jd);
                k->add(jd);
                break;
               }
        case 4:
               { 
                blockade* jd=new blockade();
                jd->validate(jd);
                k->add(jd);
                break;
               }
        case 5:
               { 
                airlift* jd=new airlift();
                jd->validate(jd);
                k->add(jd);
                break;
               }
        case 6:
               {
                negotiate* jd=new negotiate();
                jd->validate(jd);
                k->add(jd);
                break;
               }
        case 7:
              {
                  check = false;
                  break;}
       /* case 3:
        case 4:
        case 5:
        case 6:*/
        
   }}
   
    std::cout<<"number of cards : "<<k->listsize()<<std::endl;
    for(int i=0;i<k->listsize();i++){
        std::cout<<k->invoke(i)<<std::endl;
    }
    std::cout<<"checking execution method...."<<std::endl;
    for(int i=0;i<k->listsize();i++){
        k->invoke(i)->execute(k->invoke(i));
    }
    std::cout<<"delete which one?";
    int threa ;
    std::cin>>threa;
  //  std::cout<<k->list[3]<<std::endl<<std::endl;
    k->removal(threa);
    std::cout<<"after cancellization:"<<std::endl;
    for(int i=0;i<k->listsize();i++){
        std::cout<<k->invoke(i)<<std::endl;
    }
    std::cout<<"move which one to where?";
    int old;
    int new1;
    std::cin>>old;
    std::cout<<"move "<<old<<" to ? ";
    std::cin>>new1;
    std::cout<<"move "<<old<<" to "<<new1<<std::endl;
    k->move(old,new1);
     for(int i=0;i<k->listsize();i++){
        std::cout<<k->invoke(i)<<std::endl;
    }
    delete k;
    k=NULL;//delete 
    
    
    //std::cout<<jd->name;
    //vector<order*>list1={o1,o2};
    //cout << *list1[1]<<endl;
    //cout<<*o2;
   // return 0;
    
}; // Write C++ code her








