#include "Player.h"
#include "Orders.h"
#include "Card.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm> 
#include <sstream>
int testPlayers() 
{
    cout<<"\n\nPart 2:Player"<<endl;
    cout<<"----------------------------------------------------------------------"<<endl;
    vector<Territory*> t;
    vector<Continent*> co;
    vector<Card*> ca;
    vector<Order*> o;
    string name = "xuz";
    cout<<"Player owns a collection of territories \n---------------------------------"<<endl;
	string a = "canada";
	string b = "usa";
    a=b;
	t.push_back(&a);
	t.push_back(&b);
    cout<<"Player owns a hand of Warzone cards \n---------------------------------"<<endl;
	vector<string*> card;
	string c = "bomb";
	string d = "reinforcement";
	card.push_back(&c);
	card.push_back(&d);
    cout<<"\nCreating Hand object \n---------------------------------" <<endl;
	Player* a1 = new Player(t,co,ca,o,name);
    (*a1).toAttack();
	(*a1).toDeffend();
	(*a1).issueOrder("attack");
	(*a1).issueOrder("defend");
	(*a1).printOrder();
	Player* a2 = new Player(*a1);
	(*a2).toAttack();
    cout << endl;
}
