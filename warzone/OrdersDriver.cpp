#include <iostream>
#include <vector>
#include <string>
#include "Orders.h"
#include "Player.h"
#include "Map.h"
#include "Card.h"
using namespace std;

void testOrderExecution()
{
    //    std::cout << "ass big aiyushan" << std::endl;
    int NUMBEROFARMY = 10; // add army
    Territory *A1 = new Territory("A1");
    int ownarmy = 150;
    int targetarmy = 200;
    A1->setNumberOfArmies(targetarmy);
    Territory *A2 = new Territory("A2");
    A2->setNumberOfArmies(ownarmy);
    OrderList *OL1 = new OrderList();
    OrderList *OL2 = new OrderList();
    vector<Territory *> T1;
    T1.push_back(A2);
    vector<Territory *> T2;
    T2.push_back(A1);
    Hand *H = new Hand();
    Player *P1 = new Player(T1, H, "P1", OL1);
    Player *P2 = new Player(T2, H, "P2", OL2);
    // creating orders:
    //*************************************************
    // need to set the owner of the terotery.
    A2->setOwner(P1);
    A1->setOwner(P2);
    //#1 deploy
    // 8888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888

    //***********when TERROR NOT BELOG TO THE PLAYER
  /*      Deploy *deploy = new Deploy(NUMBEROFARMY, P2, A2);
        OL1->addOrders(deploy);
        deploy->execute();
        deploy->~Deploy();*/
    //**********when belongs to
        std::cout << "*************Deploy class******************"<<std::endl;
        Deploy *deploy = new Deploy(NUMBEROFARMY, P1, A2);
        OL1->addOrders(deploy);
        std::cout << "*****Execution method*****"<<std::endl;
        deploy->execute();
        std::cout << "insertion operator : " <<deploy<<endl;
        std::cout << "Copy constructor operator : "<<endl;
        Deploy *hello = deploy;
        hello->execute();
        std::cout << "String to log : "<<hello->stringToLog()<<endl;
       hello->~Deploy();
    //#2 advance
    // 8888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888
    
    std::cout << "*************Advance class******************" << std::endl;
    Advance *advance = new Advance(A2, A1, P1, NUMBEROFARMY);
    Advance *fe = new Advance(*advance);
    std::cout << fe->getName() << std::endl;
    std::cout << advance->getName() << std::endl;
    std::cout << "*****************************" << std::endl;
    std::cout << "number of terriotories in the Player: " << P1->getTerriotory().size() << std::endl;
    fe->execute();
    std::cout << "Name of target terory now belongs to : " << A1->getOwner()->getName() << std::endl;
    std::cout << "***outcome***" << std::endl;
    std::cout << "own tero previously has: " << ownarmy << ",now has: " << A2->getNumberOfArmies() << std::endl;
    std::cout << "target tero previously has: " << targetarmy << ",conquer tero now has: " << A1->getNumberOfArmies() << std::endl;
    std::cout << "number of terriotories in the Player: " << P1->getTerriotory().size() << std::endl;
    
    // 8888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888
    
    std::cout << "*************Airlift*************" << endl;
    Airlift *airlift = new Airlift(P1, A1, A2);
    std::cout << &airlift << endl;
    std::cout << &fe << endl;
    A1->setOwner(P1);
    airlift->execute();
    
    // 8888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888
    
        std::cout << "*************Bomb*************" << endl;
        Bomb *bomb = new Bomb(P1, A1, &NUMBEROFARMY);
        A1->addNeighbour(A2);
        std::cout << "Neighbours of A1: ";
        A1->showNeighbours();
        std::cout << "Neighbours of A2: ";
        A2->showNeighbours();
        bomb->execute();
    
    // 8888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888
    
     std::cout << "*************Bomb*************" << endl;
          Blockade* blockade= new Blockade(P1,A1);
         blockade->execute();
     
    // 8888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888
    std::cout << "*************Bomb*************" << endl;
    Negotiate *negotiate = new Negotiate(P1, P2);
    negotiate->execute();
    std::cout<<"The attackban list of P1: " <<P1->attackban.at(0)->getName()  << endl;
     //g++ -std=c++11  Orders.cpp Player.cpp Card.cpp Orderdriver.cpp Map.cpp
     
}