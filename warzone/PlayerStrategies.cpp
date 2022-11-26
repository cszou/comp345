#include "PlayerStrategies.h"
#include "Player.h"
#include <iostream>
#include <string>
using namespace std;

//PlayerStrategy Base Class
//----------------------------------------------------------
PlayerStrategy::PlayerStrategy(Player* player){
    this->p = player;
}

//AggressivePlayerStrategy 
//----------------------------------------------------------
AggressivePlayerStrategy::AggressivePlayerStrategy(Player* player):PlayerStrategy (player){
    strategyName = "AggressivePlayer";
}

//NeutralPlayerStrategy
//----------------------------------------------------------
NeutralPlayerStrategy::NeutralPlayerStrategy(Player* player):PlayerStrategy (player){
    strategyName ="Neutral Player";
}
string NeutralPlayerStrategy::getStrategyName(){
    return this->strategyName;
}

void NeutralPlayerStrategy:: issueOrder(string orderName){

    cout<<"Excecuting isssue order from "<<getStrategyName()<<endl;
    
    //when NeutralPlayer is attacked, it becomes AggressivePlayer
    p->setPlayerStrategy(new AggressivePlayerStrategy(p));




}
vector<Territory*> NeutralPlayerStrategy::toAttack(){

}
vector<Territory*> NeutralPlayerStrategy::toDedend(){
    
}
//----------------------------------------------------------
