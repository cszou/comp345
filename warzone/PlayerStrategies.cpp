#include "PlayerStrategies.h"
#include "Player.h"
#include <iostream>
#include <string>
using namespace std;

//PlayerStrategy Base Class
//--------------------------------------------------------------------
PlayerStrategy::PlayerStrategy(Player* player){
    this->p = player;
}

//NeutralPlayerStrategy
//--------------------------------------------------------------------
NeutralPlayerStrategy::NeutralPlayerStrategy(string strategy_Name,Player* player):PlayerStrategy (player){
    strategyName = strategy_Name;
}
string NeutralPlayerStrategy::getStrategyName(){
    return this->strategyName;
}

void NeutralPlayerStrategy:: issueOrder(string orderName){

    cout<<"Excecuting isssue order from "<<getStrategyName()<<endl;





}
vector<Territory*> NeutralPlayerStrategy::toAttack(){

}
vector<Territory*> NeutralPlayerStrategy::toDedend(){
    
}
//--------------------------------------------------------------------
