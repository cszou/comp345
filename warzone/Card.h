#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm> 
#include "Player.h"
#include "Orders.h"
#include "Map.h"
using namespace std;
class Deck;
class Player;
class Territory;
class OrdersList;

class Card{
public:
    Card();//Defalut Constructor  
    Card(string cardType);//Constructor with one parameter
    ~Card();//Destructor  
    Card(const Card &c); //Copy constructor   
    Card& operator = (const Card& c);//Assignment operator 
    void set_cardType(int num); //Set card type, from 0-4
    string get_cardType();//Get card type
    //Play method that creates an order and adds it to the player's list of order
    //Then return the card the the deck
    void play(Deck* deckCards,int* army, Player* player1,Player* player2,Territory* OLD,Territory* NEW);
    //Helper method that creates an order and adds it to the player's list of order
    void AddCardOrderToList(string cardType,int* army, Player* player1,Player* player2,Territory* OLD,Territory* NEW);
        
private:
    friend ostream & operator << (ostream &out, const Card &c);//Stream insertion operator 
    string cardType;//Storing type of the card
};

class Deck{
    public:  
    Deck();//Defalut Constructor
    ~Deck(); //Destructor
    Deck(const Deck &d);//Copy constructor
    Deck& operator = (const Deck& d); //Assignment operator
    void set_deckOfCards();//initial deck of Cards which have 3 of each, total of 15 cards
    //add card to the deck, for returning the played card to the deck
    void add_CardsToDeck(Card* aCard);
    //draw method that draw a random crad from remaining in the deck and return it to the hand of cards
    Card* draw(); 

private:
    vector<Card*> deckOfCards;//The vector which contain a finite collection of cards 
    Card* drawCard;
    friend ostream & operator << (ostream &out, const Deck &d);//Stream insertion operator 
};

class Hand{
    public:
    Hand();//Defalut Constructor
    Hand(int num);
    ~Hand(); //Destructor
    Hand(const Hand &h); //Copy constructor
    Hand& operator = (const Hand& h); //Assignment operator
    int numOfHandCards();//method that return the number of cards in hand
    vector<Card*> get_VectorOfHand();//get the vector of cards in hand
    void add_CardinHand(Card* cardFromDeck);//add cards into hand from the deck of cards
    void remove_CardinHand();
    void remove_CardinHand_ByType(string type); // remove the first card in hand that has the input type

private:
    vector<Card*> CardsinHand;
     friend ostream & operator << (ostream &out, const Hand &h);//Stream insertion operator 
};
