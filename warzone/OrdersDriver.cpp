#include <iostream>
#include<vector>
#include<string>
#include"Orders.h"

void testOrdersLists(){

    std::cout << "\nPart 3: Orders list" << std::endl;
    bool check = true;
    int orderfind;
    orderlist* k= new orderlist();
    //std::cout<<"using copy constructor!"<<std::endl;
    std::cout<<*k<<std::endl;
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
     orderlist* k1 =new orderlist(*k);
     std::cout<<"the order of original pointer:"<<k<<std::endl;
     std::cout<<"the order of deep copyed pointer:"<<k1<<std::endl;

    std::cout<<"checking execution method...."<<std::endl;
    for(int i=0;i<k1->listsize();i++){
        k1->invoke(i)->execute(k1->invoke(i));
    }
    std::cout<<"delete which one?";
    int threa ;
    std::cin>>threa;
  //  std::cout<<k->list[3]<<std::endl<<std::endl;
    k1->removal(threa);
    std::cout<<"after cancellization:"<<std::endl;
    for(int i=0;i<k1->listsize();i++){
        std::cout<<k1->invoke(i)<<std::endl;
    }
    std::cout<<"move which one to where?";
    int old;
    int new1;
    std::cin>>old;
    std::cout<<"move "<<old<<" to ? ";
    std::cin>>new1;
    std::cout<<"move "<<old<<" to "<<new1<<std::endl;
    k1->move(old,new1);
     for(int i=0;i<k1->listsize();i++){
        std::cout<<k1->invoke(i)<<std::endl;
    }
    delete k1;
    k1=NULL;//delete
    std::cout << "Orders list demo end." << std::endl << std::endl;
    
}