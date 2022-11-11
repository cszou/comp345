#include <iostream>
#include<vector>
#include<string>
#include"Orders.h"
#include"Player.h"
#include"Map.h"

    Order::Order(){
        std::cout<<"order created..."<<std::endl;
    }
    Order::~Order(){
    }//destructor
     std::string Order:: call(){
        return 0;
     }
     void Order::execute(){};
    std::string Order:: description(){
         return "it use for";
    }//no need maybe
    Order::Order(const Order& e) {//copy consrtuctor
}

	string stringToLog(){
	 return " ";
	}
//------------------------------------------------    
    Deploy::Deploy(int* NUMBEROFARMY,Player* K,Territory* F){
        this->K=K;
        this->F=F;
        this->NUMBEROFARMY=NUMBEROFARMY;
       std::cout<<"initiate deploy!"<<std::endl;
    }
    Deploy::~Deploy(){
      std::cout<<"deploy class destruction called"<<std::endl;
      //add logobserver
    }
    bool Deploy::validate(){
        if(K!=F->getOwner())
        return false;
        else
        return true;
    }
    void Deploy::execute(){
        if(validate()){
           std::cout<<"The terriotery is : "+F->getName()<<std::endl;
           std::cout<<"Previously has army: "+F->getNumberOfArmies()<<std::endl;
            F->setNumberOfArmies(F->getNumberOfArmies()+*NUMBEROFARMY);
            std::cout<<"Now has army: "+F->getNumberOfArmies()<<std::endl;
            *check=true;
        }else{
                        std::cout<<"Execute unsuccessful since validated false."<<std::endl;
        }
         Notify(this);
    }
    Deploy::Deploy(const Deploy& s){
         this->F=new Territory(*(s.F));
         this->K=new Player(*(s.K));
    }
    Deploy& Deploy::operator=(const Deploy& s) {//assignment operator
    if(this!=&s){
        this->F=new Territory(*(s.F));
        this->K=new Player(*(s.K));
        std::cout<<"assignment operator initiated"<<std::endl;
        return *this;
    }
    return *this;
    }
    std::ostream& operator<<(std::ostream &s,  Deploy* deploy) {
        if((deploy)->check)
          return s << "This is a deploy order,and it's executed."<<std::endl;//string insertion operator
        else
          return s<<"This is a deploy order and it has not been executed."<<std::endl;
}
	string stringToLog(){
		return "Order Executed: " + name;
	{
	//-------------------------------ADVANCE-------------------------------------------------------
    Advance::Advance(Territory *old,Territory *new1,Player *player,int* NUMBEROFARMY){
        this->OLD=old;
        this->NEW=new1;
        this->NUMBEROFARMY=NUMBEROFARMY;
        this->K=player;
        std::cout<<"initiate advance!"<<std::endl;
    }
    Advance::~Advance(){
         std::cout<<"advance class destruction called"<<std::endl;
         //detach()
    }

    bool Advance::validate(){
        for(Territory* i:OLD->getNeighbours()){
                if (&NEW==&i)//if new is not neibor of old
                return false;}
        if(OLD->getOwner()!=K){
            return false;
        }else
            return true;
    }
    void Advance::execute(){
        if(validate())
        {
            if(OLD->getOwner()==NEW->getOwner()){
            std::cout<<"ARMY FROM OLD PLACE:"+OLD->getNumberOfArmies()<<std::endl;
            std::cout<<"ARMY FROM NEW PLACE:"+NEW->getNumberOfArmies()<<std::endl;
             NEW->setNumberOfArmies(NEW->getNumberOfArmies()+OLD->getNumberOfArmies());
            std::cout<<"UPDATE! ARMY FROM NEW PLACE:"+NEW->getNumberOfArmies()<<std::endl;
            }//SAME OWNER BETWEEN TEROIRO
            else/*OLD->getOwner()!=NEW->getOwner()*/{//attack
            if(OLD->getNumberOfArmies()*0.6>NEW->getNumberOfArmies()){
                NEW->setNumberOfArmies(OLD->getNumberOfArmies()-0.7*NEW->getNumberOfArmies());
                OLD->setNumberOfArmies(0);
                NEW->setOwner(OLD->getOwner());//owner changed!
                if (numberoftime==0)
                OLD->getOwner()->gethandofcard()->add_CardinHand(d->draw());//add card in hand
                else
                std::cout<<"no new card will give,since more than one advance sofar!"<<std::endl;
                std::cout<<"advance successfully,swonp in!"<<std::endl;
            }else if(NEW->getNumberOfArmies()*0.7<OLD->getNumberOfArmies()&&OLD->getNumberOfArmies()*0.6<NEW->getNumberOfArmies())
            {
                //old 150 new 200
                int nold =OLD->getNumberOfArmies();
                int nnew =NEW->getNumberOfArmies();
                OLD->setNumberOfArmies(nold-nnew*0.7);
                NEW->setNumberOfArmies(nnew-nold*0.6);
                std::cout<<"half half both got damaged"<<std::endl;
            }else if(NEW->getNumberOfArmies()*0.7>=OLD->getNumberOfArmies()){
                //new 20 old 130
                NEW->setNumberOfArmies(NEW->getNumberOfArmies()-OLD->getNumberOfArmies()*0.6);
                OLD->setNumberOfArmies(0);
                std::cout<<"target cant make,own tero become 0"<<std::endl;
            }else
                std::cout<<"dont know whats the condition"<<std::endl;
            }        
        std::cout<<"advance order validated!"<<std::endl;
	 Notify(this);
    }

 //   Advance::Advance(const Advance& s){
}
    Advance& Advance::operator=(const Advance& s) {//assignment operator
    Order::operator= (s);
    return *this;
}
    std::ostream& operator<<(std::ostream &s,  Advance *i) {
    return s << "Advance order meaning: To move forward"<<std::endl;//string insertion operator
}
    string stringToLog(){
		return "Order Executed: " + name;
	{
//-----------------------------------Airlift-----------------------
    Airlift::Airlift(Player *K,Territory *OLD,Territory *NEW){
        this->OLD=OLD;
        this->NEW=NEW;
        this->K=K;
       std::cout<<"initiate airlift!"<<std::endl;
    }
    Airlift::~Airlift(){
       std::cout<<"airlift class destruction called"<<std::endl;
    }

    bool Airlift::validate(){
        if(OLD->getOwner()!=NEW->getOwner())
        {
        std::cout<<"airlift order validated!"<<std::endl;
        return false;}
        else {
        return true;
        std::cout<<"airlift order validated!"<<std::endl;}
    }
    void Airlift::execute(){
        if(validate()){
            std::cout<<"source terriotery,currently: "+OLD->getNumberOfArmies()<<std::endl;
            std::cout<<"target terriotery,currently: "+NEW->getNumberOfArmies()<<std::endl;
            int number;
            std::cout<<"choose the amount of army from source terriotery,currently: "+OLD->getNumberOfArmies()<<std::endl;
            std::cin>>number;
            if(0<=number&&number<=OLD->getNumberOfArmies()){
                NEW->setNumberOfArmies(NEW->getNumberOfArmies()+number);
                std::cout<<"UPDATE! target terriotery : "+NEW->getNumberOfArmies()<<std::endl;
            }else
            std::cout<<"cannot execute since validation failded"<<std::endl;            
        }
        std::cout<<"airlift order executed!"<<std::endl;
    }
    Airlift::Airlift(const Airlift& s) : Order(s) {
    }
    Airlift& Airlift::operator=(const Airlift& s) {//assignment operator
    Order::operator= (s);
    return *this;
    }
    std::ostream& operator<<(std::ostream &s,  Airlift *i) {
    return s << "Airlift order meaning: To move supply or army by air to a specific area"<<std::endl;//string insertion operator
	Notify(this);
	
    }
    string stringToLog(){
	return "Order Executed: " + name;
	{
//-----------------------------------BOMB---------------------------
    Bomb::Bomb(Player* player,Territory* target,int* army ){
       this->NUMBEROFARMY=army;
       this->target=target;
       this->K=player;

       std::cout<<"initiate bomb!"<<std::endl;
    }
    Bomb::~Bomb(){
       std::cout<<"bomb class destruction called"<<std::endl;
    }
    bool Bomb::validate(){
        if(target->getOwner()==K)
        return false;
        bool verif = false;
        for(auto it:target->getNeighbours()){
            if(K->ownsTerritory(it))
             verif=true;
        }
        if(!verif)
        return false;
        std::cout<<"bomb order valid"<<endl;
    }
    void Bomb::execute(){
        if(validate()){
            int record =target->getNumberOfArmies();
            target->setNumberOfArmies(target->getNumberOfArmies()/2);
            std::cout<<"bomb order executed!Previous target army: "+record<<",Currently target terriotery army: "+target->getNumberOfArmies()<<std::endl;
        }
        std::cout<<"bomb order executed!"<<std::endl;
	  Notify(this);
    }
     string stringToLog(){
	return "Order Executed: " + name;
	{
		
    Bomb::Bomb(const Bomb& s) : Order(s) {
}
    Bomb& Bomb::operator=(const Bomb& s) {//assignment operator
    Order::operator= (s);
    return *this;
}
    std::ostream& operator<<(std::ostream &s,  Bomb *i) {
    return s << "Bomb order meaning: To air raid specific area"<<std::endl;//string insertion operator
}
//---------------------------------------Blockade
    Blockade::Blockade(Player* k,Territory* target){
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
	  Notify(this);
    }
    Blockade::Blockade(const Blockade& s) : Order(s) {
}
    Blockade& Blockade::operator=(const Blockade& s) {//assignment operator
    Order::operator= (s);
    return *this;
}
       std::ostream& operator<<(std::ostream &s,  Blockade *i) {
    return s << "Blockade order meaning: To block a specific area"<<std::endl;//string insertion operator
}

    
//-----------------------------------Negotiate---------------------------
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
	   Notify(this);
    }
    Negotiate::Negotiate(const Negotiate& s) : Order(s) {
}
    Negotiate& Negotiate::operator=(const Negotiate& s) {//assignment operator
    Order::operator= (s);
    return *this;
}
    std::ostream& operator<<(std::ostream &s,  Negotiate *i) {
    return s << "Negotiate order meaning: To negociate with the rebel or other players"<<std::endl;//string insertion operator
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
OrderList & OrderList:: operator = (const OrderList& d){//assignment operator
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
	    Notify(this);
    }
        std::ostream& operator<<(std::ostream& s, OrderList& ol)//string insertion operator for orderlists
    {
        return s << "This is a list of orders." << std::endl;
    }
	
	string OrderList :: stringToLog(){
   	 return  "Order Issued:" ;
	}
int main(){
    int NUMBEROFARMY =13;
    Territory* A1= new Territory("A1");
    Territory* A2= new Territory("A2");
    Territory* A3= new Territory("A3");
    Territory* A4= new Territory("A4");
    A1->addNeighbour(A2);
    A1->addNeighbour(A3);
    A2->addNeighbour(A1);
    A2->addNeighbour(A4);
    Deck *d = new Deck();
    Hand* h = new Hand();
    Player* K =new Player({A2,A1},h,"SB");
    //add new one to hand ;
    h->add_CardinHand(d->draw());

    Territory* F;


    Order* k = new Deploy(&NUMBEROFARMY,K,F);
    OrderList* k1 =new OrderList();
    k1->add(k);

}
