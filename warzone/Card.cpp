#include "Card.h"
#include "Orders.h"
#include "Map.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <algorithm>
using namespace std;
class OrderList;
class Player;

//Defalut Constructor 
Card::Card(){
}
//Constructor with one parameter
Card::Card(string cardType){
    cardType = cardType;
}
//Destructor  
Card::~Card(){
}
//Copy constructor   
Card::Card(const Card &c){
    cardType = c.cardType;
}
//Assignment operator 
Card & Card ::operator = (const Card& c){
    cardType = c.cardType;
    return *this;
}
string Card:: get_cardType(){
    return cardType;
}
//Set card type, from 0-4
void Card:: set_cardType(int num){
    switch (num)
    {
    case 1:
        cardType="bomb" ;
        break;
    case 2:
        cardType="reinforcement";
        break;
    case 3:
         cardType="blockade";
        break;
    case 4:
         cardType="airlift";
        break;
    case 5:
         cardType="diplomacy";
        break;
    }
}
//Play method that creates an order and adds it to the player's list of order
//Then return the card the the deck
void Card:: play(Deck* deckCards,int* army, Player* player1,Player* player2,Territory* OLD,Territory* NEW ){
    deckCards->add_CardsToDeck(this);
    AddCardOrderToList(this->get_cardType(),army,player1,player2,OLD,NEW);
    }

//Helper method that creates an order and adds it to the player's list of order
void Card:: AddCardOrderToList(string const cardTypeAdd,int* army, Player* player1,Player* player2,Territory* OLD,Territory* NEW){
    if(cardTypeAdd == "bomb"){
        player1->getlist()->addOrders(new Bomb(player1,OLD,army));
    }
    else if(cardTypeAdd == "blockade"){
         player1->getlist()->addOrders(new Blockade(player1 ,OLD));
    }
    else if(cardTypeAdd == "airlift"){
         player1->getlist()->addOrders(new Airlift(player1 ,OLD ,NEW));
    }
    else if(cardTypeAdd == "diplomacy"){
         player1->getlist()->addOrders(new Negotiate(player1 , player2));
    }
    else{
        cout<<"Invalid card"<<endl;
    }
 } 
//Stream insertion operator 
ostream& operator << (ostream & strm, const Card &c){
    return strm << c.cardType;
}

//Deck Class
//-------------------------------------------------------------------
//Defalut Constructor
Deck::Deck(){
    this->set_deckOfCards();
}
//Destructor
Deck::~Deck(){
   for(int i = 0; i<deckOfCards.size();i++){
        delete deckOfCards.at(i);
   }
   deckOfCards.clear();
   
}
//Copy constructor
Deck::Deck(const Deck &d){
    deckOfCards = *new vector <Card*> (d.deckOfCards);
    for(int i = 0;i< d.deckOfCards.size();i++){
         deckOfCards.push_back(new Card(*d.deckOfCards[i]));
    }
}
//Assignment operator
Deck & Deck:: operator = (const Deck& d){
    deckOfCards.reserve(deckOfCards.size());
    for(int i = 0;i< d.deckOfCards.size();i++){
        deckOfCards.push_back(new Card(*d.deckOfCards[i]));
    }
    return *this;
}
//Stream insertion operator 
ostream& operator << (ostream & strm, const Deck &d){
    strm<<"The Deck of cards have "<< d.deckOfCards.size() << " cards" <<endl;
    for(int i = 0; i<d.deckOfCards.size(); i++){
        strm<< i+1 <<": "<< *d.deckOfCards.at(i) << endl;
    }
    return strm;
}

//initial deck of Cards which have 3 of each, total of 15 cards
void Deck:: set_deckOfCards(){
    //three kind of each
    for(int i = 0;i<3;i++){
        for (int j = 1;j<=5;j++){
            Card* c = new Card;
            c->set_cardType(j);
            deckOfCards.push_back(c);
        }
    }
}
//add card to the deck, for returning the played card to the deck
void Deck::add_CardsToDeck(Card* aCard){
     deckOfCards.push_back(new Card(*aCard));
     delete aCard;
}
//draw method that draw a random crad from remaining in the deck and return it to the hand of cards
Card* Deck:: draw(){
    srand(time(0));
    int random = rand()% (deckOfCards.size());
    Card* drawCard = deckOfCards.at(random);//copy random picked card
    //generate random number from 0 to number of cards in deck-1
    deckOfCards.erase(deckOfCards.begin()+random);//erase drawn card from the vector
    //std::cout<<"draw method finished"<<std::endl;
    return drawCard;
 }

//Hand Class
//--------------------------------------------------------------

//Defalut Constructor
Hand::Hand(){
//std::cout<<"Hand created"<<endl;
}
//Destructor
Hand::~Hand(){
for(int i = 0; i< CardsinHand.size();i++){
        delete  CardsinHand.at(i);
   }
    CardsinHand.clear();
}
//Copy constructor
Hand:: Hand(const Hand &h){
    CardsinHand.reserve(CardsinHand.size());
    for(int i = 0;i< h.CardsinHand.size();i++){
        CardsinHand.push_back(new Card(*h.CardsinHand[i]));
    }
}
//Assignment operator
Hand & Hand:: operator = (const Hand& h){
    CardsinHand.reserve(CardsinHand.size());
    for(int i = 0;i< h.CardsinHand.size();i++){
        CardsinHand.push_back(new Card(*h.CardsinHand[i]));
    }
    return *this;
}
//method that return the number of cards in hand
int Hand:: numOfHandCards(){
    return CardsinHand.size();
}
//get the vector of cards in hand
vector<Card*> Hand:: get_VectorOfHand(){
    return CardsinHand;
}
//add cards into hand from the deck of cards
void Hand:: add_CardinHand(Card* cardFromDeck){
    CardsinHand.reserve(1);
    CardsinHand.push_back(new Card(*cardFromDeck));
    delete cardFromDeck;
}
//Removing cards from player's hand after invoking play method
void Hand:: remove_CardinHand(){
    CardsinHand.clear();
}
//Stream insertion operator 
ostream& operator << (ostream & strm, const Hand &h){
    if (h.CardsinHand.empty()){
        return strm <<"\nNo more cards in hand!"<<endl;
    }
    else{
    strm << "\nPlayer's hand now have card: "<<endl;
     for(int i = 0;i < h.CardsinHand.size();i++){
        cout<<*h.CardsinHand.at(i) <<" , ";
    }
    cout<< endl;
    return strm;
    }
}

void Hand::remove_CardinHand_ByType(string type) {
    for (int i = 0; i < CardsinHand.size(); i++) {
        if (CardsinHand[i]->get_cardType() == type) {
            CardsinHand.erase(CardsinHand.begin() + i);
        }
    }

}
