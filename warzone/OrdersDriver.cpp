#include <iostream>
#include<vector>
#include<string>
#include"Orders.h"

void testOrdersLists() {

	std::cout << "\nPart 3: Orders list" << std::endl;
	bool check = true;
	int orderfind;
	OrderList* k = new OrderList();
	std::cout << *k << std::endl;//this is a list of orders
	while (check) {
		std::cout << "which order you want to create? 1.advance;2.deploy;3.bomb;4.blockade;5.airlift;6.negotiate;7.non" << std::endl;
		std::cin >> orderfind;
		switch (orderfind) {
		case 1:
		{
			Advance* jd = new Advance();
			std::cout<<jd;
			jd->validate(jd);//description needs,stream insertion operator for each sub class.
			k->add(jd);
			break;
		}
		case 2:
		{
			Deploy* jd = new Deploy();
			std::cout<<jd;
			jd->validate(jd);
			k->add(jd);
			break;
		}
		case 3:
		{
			Bomb* jd = new Bomb();
			std::cout<<jd;
			jd->validate(jd);
			k->add(jd);
			break;
		}
		case 4:
		{
			Blockade* jd = new Blockade();
			std::cout<<jd;
			jd->validate(jd);
			k->add(jd);
			break;
		}
		case 5:
		{
			Airlift* jd = new Airlift();
			std::cout<<jd;
			jd->validate(jd);
			k->add(jd);
			break;
		}
		case 6:
		{
			Negotiate* jd = new Negotiate();
			std::cout<<jd;
			jd->validate(jd);
			k->add(jd);
			break;
		}
		case 7:
		{
			check = false;
			break;}
		}
	}
	std::cout << "number of cards : " << k->listsize() << std::endl;
	for (int i = 0;i < k->listsize();i++) {
		std::cout << k->invoke(i) << std::endl;
	}
	OrderList* k1 = new OrderList(*k);//copy constructor
	std::cout << "the order of original pointer:" << k << std::endl;
	std::cout << "the order of deep copyed pointer:" << k1 << std::endl;

	std::cout << "checking execution method...." << std::endl;
	for (int i = 0;i < k1->listsize();i++) {
		k1->invoke(i)->execute(k1->invoke(i));
	}
	bool cont = true;//remove method
		std::cout << "delete which one?";
		int threa;
		while (cont) {
			std::cin >> threa;
			if (threa > k1->listsize())
				std::cout << "Out of bound. Please try again." << std::endl;
			else
				cont = false;
		}
		k1->removal(threa);
		std::cout << "after cancellization:" << std::endl;
		for (int i = 0;i < k1->listsize();i++) {
			std::cout << k1->invoke(i) << std::endl;
		}
	int old;
	int new1;
	cont = true;
	while(cont) {
		std::cout << "move which one to where?";
		std::cin >> old;
		std::cout << "move " << old << " to ? ";
		std::cin >> new1;
		std::cout << "move " << old << " to " << new1 << std::endl;
		if(old>k1->listsize()||new1>k1->listsize())
			std::cout << "Out of bound. Please try again." << std::endl;
		else
			cont = false;
	}
	k1->move(old, new1);
	for (int i = 0;i < k1->listsize();i++) {//move method 
		std::cout << k1->invoke(i) << std::endl;
	}
	delete k1;
	k1 = NULL;//avoid memory leaks
	std::cout << "Orders list demo end." << std::endl << std::endl;
}
int main(){
	testOrdersLists();
}