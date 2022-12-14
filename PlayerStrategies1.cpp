#include "PlayerStrategies.h"
#include "Player.h"
#include <iostream>
#include <string>
#include "Orders.h"
#include "Card.h"
#include "Map.h"
#include <iostream>
using std::cin;
using std::cout;
#include <fstream>
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <algorithm>
#include <sstream>
using namespace std;

// PlayerStrategy Base Class
//----------------------------------------------------------
PlayerStrategy::PlayerStrategy(Player *player)
{
    this->p = player;
}

// HumanPlayerStrategy
//----------------------------------------------------------
HumanPlayerStrategy::HumanPlayerStrategy(Player *player) : PlayerStrategy(player)
{
    strategyName = "HumanPlayer";
}

void HumanPlayerStrategy::issueOrder(string orderName)
{
    p->set_Deploy_Territories();
    p->set_Available_Territories();
    cout << "Order Issuing phase for player " << strategyName << endl;
    bool finished = false;
    // Case deploy
    if (orderName == "Deploy")
    {
        cout << "Please enter a deployement order" << endl;
        cout << "Your territories are: ";
        for (auto t : p->getTerriotory())
            cout << t->getName() << "  ";
        cout << endl;
        cout << "You have " << p->getReinforcement() << " troops left in your reinforcement tool, please enter the number of troops you want to use" << endl;
        int num;
        cin >> num;
        while (!cin)
        {
            cout << "Wrong data type. Please try again. " << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> num;
        }
        if (num > p->getReinforcement())
        {
            num = p->getReinforcement();
        }
        cout << "Where do you want to deploy " << num << " troops? Please enter the name of the territory. " << endl;
        string name;
        cin >> name;
        while (p->getDeploy_territories().find(name) == p->getDeploy_territories().end())
        {
            cout << "Wrong name, please try again." << endl;
            cin >> name;
        }
        cout << "Order type: Deploy " << num << " -> " << name << endl;

        p->setReinforcement(p->getReinforcement() - num);

        p->addOrder(new Deploy(num, this->p, p->getDeploy_territories()[name]));

        // Execute order
        Order *o = p->getlist()->getorderlist().back();

        o->execute();

        p->getlist()->getorderlist().pop_back();

        cout << "Are you done issuing orders? (Yes/No)" << endl;
        string s;
        cin >> s;
        if (s == "Yes" && p->getReinforcement() == 0)
        {
            finished = true;
        }
    }
    else
    {
        // Other case
        vector<string> Order_names;
        Order_names.push_back("Advance");
        vector<Card *> cards = p->gethandofcard()->get_VectorOfHand();
        for (int i = 0; i < cards.size(); i++)
        {
            Order_names.push_back(cards[i]->get_cardType());
        }
        cout << "Please choose one of the options: " << endl;
        cout << "-- Advance" << endl;
        if (Order_names.size() > 1)
        {
            cout << "Use one of the cards: " << endl;
            for (int k = 1; k < Order_names.size(); k++)
            {
                cout << "-- " << Order_names[k] << endl;
            }
        }
        string input;
        cin >> input;
        while (find(Order_names.begin(), Order_names.end(), input) == Order_names.end())
        {
            cout << "No such option, try again" << endl;
            cin >> input;
        }
        // Advance
        if (input == "Advance")
        {
            cout << "Your territories are: ";
            for (std::map<string, Territory *>::iterator it = p->getDeploy_territories().begin(); it != p->getDeploy_territories().end(); ++it)
            {

                cout << it->first << "  ";
            }
            cout << endl;
            cout << "Choose the source territory: ";
            string source_name;
            cin >> source_name;
            while (p->getDeploy_territories().find(source_name) == p->getDeploy_territories().end())
            {
                cout << "Wrong name, please try again." << endl;
                cin >> source_name;
            }
            int army_num = p->getDeploy_territories()[source_name]->getNumberOfArmies();
            cout << "You have " << army_num << " army unites in this territory, how many do you want to move? " << endl;

            int num;
            cin >> num;
            while (!cin)
            {
                cout << "Wrong data type. Please try again. " << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> num;
            }
            if (num > army_num)
            {
                num = army_num;
            }
            cout << "Please enter the target territory: " << endl;
            cout << "The available options are your territories and the enemy territories" << endl;
            cout << "Available territories are: ";
            for (std::map<string, Territory *>::iterator it = p->getAvailable_territories().begin(); it != p->getAvailable_territories().end(); ++it)
            {

                cout << it->first << "  ";
            }
            cout << endl;
            string target_name;
            cin >> target_name;
            while (p->getAvailable_territories().find(target_name) == p->getAvailable_territories().end())
            {
                cout << "Wrong name, please try again." << endl;
                cin >> target_name;
            }
            p->addOrder(new Advance(p->getDeploy_territories()[source_name], p->getAvailable_territories()[target_name], this->p, num));
        }

        // Bomb card
        else if (input == "bomb")
        {
            cout << "Using the bomb card, please choose a territory" << endl;
            cout << "Available territories are: ";
            for (std::map<string, Territory *>::iterator it = p->getAvailable_territories().begin(); it != p->getAvailable_territories().end(); ++it)
            {

                cout << it->first << "  ";
            }
            string target_name;
            cin >> target_name;
            while (p->getAvailable_territories().find(target_name) == p->getAvailable_territories().end())
            {
                cout << "Wrong name, please try again." << endl;
                cin >> target_name;
            }
            p->addOrder(new Bomb(this->p, p->getAvailable_territories()[target_name], 0));
            p->gethandofcard()->remove_CardinHand_ByType("bomb");
        }

        if (input == "blockade")
        {
            cout << "Using the bomb card, please choose one of your territory" << endl;
            cout << "Available territories are: ";
            for (std::map<string, Territory *>::iterator it = p->getDeploy_territories().begin(); it != p->getDeploy_territories().end(); ++it)
            {

                cout << it->first << "  ";
            }
            string target_name;
            cin >> target_name;
            while (p->getDeploy_territories().find(target_name) == p->getDeploy_territories().end())
            {
                cout << "Wrong name, please try again." << endl;
                cin >> target_name;
            }
            p->addOrder(new Blockade(this->p, p->getAvailable_territories()[target_name]));
            p->gethandofcard()->remove_CardinHand_ByType("blockade");
        }

        // Air Lift
        else if (input == "airlift")
        {
            cout << "Using this airlift card" << endl;
            cout << "Your territories are: ";
            for (std::map<string, Territory *>::iterator it = p->getDeploy_territories().begin(); it != p->getDeploy_territories().end(); ++it)
            {

                cout << it->first << "  ";
            }
            cout << "Choose the source territory";
            string source_name;
            cin >> source_name;
            while (p->getDeploy_territories().find(source_name) == p->getDeploy_territories().end())
            {
                cout << "Wrong name, please try again." << endl;
                cin >> source_name;
            }
            int army_num = p->getDeploy_territories()[source_name]->getNumberOfArmies();
            cout << "You have " << army_num << "army unites in this territory, how many do you want to move ?" << endl;

            int num;
            cin >> num;
            while (!cin)
            {
                cout << "Wrong data type. Please try again. " << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> num;
            }
            if (num > army_num)
            {
                num = army_num;
            }
            cout << "Please enter the target territory" << endl;
            cout << "The available options are your territories and the enemy territories" << endl;
            cout << "Available territories are: ";
            for (std::map<string, Territory *>::iterator it = p->getDeploy_territories().begin(); it != p->getDeploy_territories().end(); ++it)
            {

                cout << it->first << "  ";
            }
            string target_name;
            cin >> target_name;
            while (p->getDeploy_territories().find(target_name) == p->getDeploy_territories().end())
            {
                cout << "Wrong name, please try again." << endl;
                cin >> target_name;
            }

            p->addOrder(new Airlift(this->p, p->getDeploy_territories()[source_name], p->getDeploy_territories()[target_name]));
            p->gethandofcard()->remove_CardinHand_ByType("airlift");
        }
        else if (input == "diplomacy")
        {
            cout << "Using diplomacy card" << endl;
            cout << "Please choose a victim" << endl;
            cout << "The available players are: ";
            for (std::map<string, Player *>::iterator it = p->getPlayers_Map().begin(); it != p->getPlayers_Map().end(); ++it)
            {
                cout << it->first << "  ";
            }
            string name;
            cin >> name;
            while (p->getPlayers_Map().find(name) == p->getPlayers_Map().end())
            {
                cout << "No such player, are you kidding me?! Try again";
                cin >> name;
            }
            p->addOrder(new Negotiate(this->p, p->getPlayers_Map()[name]));
            p->gethandofcard()->remove_CardinHand_ByType("diplomacy");
        }

        Order *o = p->getlist()->getorderlist().back();

        o->execute();

        p->getlist()->getorderlist().pop_back();

        cout << "Are you done issuing orders? (Yes/No)" << endl;
        string s;
        cin >> s;
        if (s == "Yes" && p->getReinforcement() == 0)
        {
            finished = true;
        }
    }
}
vector<Territory *> HumanPlayerStrategy::toAttack()
{
    vector<Territory *> bannedTerritory;
    for (int i = 0; i < p->getAttackBan().size(); i++)
    {
        vector<Territory *> player_territories = p->getAttackBan()[i]->getTerriotory();
        for (int k = 0; k < player_territories.size(); k++)
        {
            Territory *t = player_territories[k];
            if (find(bannedTerritory.begin(), bannedTerritory.end(), t) == bannedTerritory.end())
            {
                bannedTerritory.push_back(t);
            }
        }
    }
    vector<Territory *> tAttack;
    for (int i = 0; i < p->getTerriotory().size(); i++)
    {
        vector<Territory *> neignbours = p->getTerriotory()[i]->getNeighbours();
        for (int k = 0; k < neignbours.size(); k++)
        {
            if ((find(tAttack.begin(), tAttack.end(), neignbours[k]) == tAttack.end()) && find(bannedTerritory.begin(), bannedTerritory.end(), neignbours[k]) == bannedTerritory.end())
            {
                tAttack.push_back(neignbours[k]);
            }
        }
    }
    for (int i = 0; i < p->getTerriotory().size(); i++)
    {
        if (find(tAttack.begin(), tAttack.end(), p->getTerriotory()[i]) == tAttack.end())
        {
            tAttack.push_back(p->getTerriotory()[i]);
        }
    }
    return tAttack;
}
vector<Territory *> HumanPlayerStrategy::toDedend()
{
    return this->p->getTerriotory();
}

// AggressivePlayerStrategy
//----------------------------------------------------------
AggressivePlayerStrategy::AggressivePlayerStrategy(Player *player) : PlayerStrategy(player)
{
    strategyName = "AggressivePlayer";
}

// NeutralPlayerStrategy
//----------------------------------------------------------

NeutralPlayerStrategy::NeutralPlayerStrategy(Player *player) : PlayerStrategy(player)
{
    strategyName = "Neutral Player";
}
string NeutralPlayerStrategy::getStrategyName()
{
    return this->strategyName;
}

void NeutralPlayerStrategy::issueOrder(string orderName)
{
    if (p->getifattacked())
    {
        // execute aggresive
    }
    cout << "Excecuting isssue order from " << getStrategyName() << endl;
}
vector<Territory *> NeutralPlayerStrategy::toAttack()
{
    if (p->getifattacked())
    {
        cout << "becomes aggresstive player since got attacked" << endl;
        vector<Territory *> deplicate = this->p->getTerriotory();
        sort(deplicate.begin(), deplicate.end(), AggressivePlayerStrategy::compareInterval); // first is weakest
        return deplicate;
        // execute aggresive
    }
    cout << "NeutralPlayerStrategy doesnt attack or defend unless got attacked" << endl;
    vector<Territory *> empty;
    return empty;
}
vector<Territory *> NeutralPlayerStrategy::toDedend()
{
    if (p->getifattacked())
    {
        cout << "becomes aggresstive player since got attacked" << endl;
        cout << "cannot defend ,return empty default vector" << endl;
        vector<Territory *> empty;
        return empty;
        // execute aggresive
    }
    cout << "cannot defend,hasnt been attacked yet,return empty default vector" << endl;
    vector<Territory *> empty;
    return empty;
}

//-------BenevolentPlayerStrategy---------------------------------------------------

BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player *player) : PlayerStrategy(player)
{
    strategyName = "Benevolent  Player";
}
string BenevolentPlayerStrategy::getStrategyName()
{
    return this->strategyName;
}

void BenevolentPlayerStrategy::issueOrder(string orderName)
{
    if (orderName == "Deploy")
    {
        std::cout << "for player " << p->getName() << ",BenevolentPlayerStrategy." << endl;
        std::cout << "deploy." << endl;
        if (p->getReinforcement() > 0)
        {
            std::cout << "the pool is " << p->getReinforcement() << endl;
            std::cout << "All goes to weakest country:" << toDedend().at(0)->getName() << endl;
            p->addOrder(new Deploy(p->getReinforcement(), p, toDedend().at(0)));
            p->setReinforcement(0);
            p->gethandofcard()->remove_CardinHand_ByType("Deploy");
        }
    }
    else if (orderName == "Advance" | orderName == "bomb")
    {
        if (orderName == "Advance")
        {
            std::cout << "advance." << endl;
            std::cout << "BenevolentPlayerStrategy doesnt advance." << endl;
            p->gethandofcard()->remove_CardinHand_ByType("Advance");
        }
        else
        {
            std::cout << "bomb." << endl;
            std::cout << "BenevolentPlayerStrategy doesnt bomb." << endl;
            p->gethandofcard()->remove_CardinHand_ByType("bomb");
        }
    }
    else
    {
        if (orderName == "airlift")
        {
            cout << "Using this airlift card" << endl;
            cout << "Your territories are: ";
            for (std::map<string, Territory *>::iterator it = p->getDeploy_territories().begin(); it != p->getDeploy_territories().end(); ++it)
            {
                cout << it->first << "  ";
            }
            cout << "Choose the source territory";
            string source_name;
            cin >> source_name;
            while (p->getDeploy_territories().find(source_name) == p->getDeploy_territories().end())
            {
                cout << "Wrong name, please try again." << endl;
                cin >> source_name;
            }
            int army_num = p->getDeploy_territories()[source_name]->getNumberOfArmies();
            cout << "You have " << army_num << "army unites in this territory, how many do you want to move ?" << endl;

            int num;
            cin >> num;
            while (!cin)
            {
                cout << "Wrong data type. Please try again. " << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> num;
            }
            if (num > army_num)
            {
                num = army_num;
            }
            cout << "Please enter the target territory" << endl;
            cout << "The available options are your territories and the enemy territories" << endl;
            cout << "Available territories are: ";
            for (std::map<string, Territory *>::iterator it = p->getDeploy_territories().begin(); it != p->getDeploy_territories().end(); ++it)
            {
                cout << it->first << "  ";
            }
            string target_name;
            cin >> target_name;
            while (p->getDeploy_territories().find(target_name) == p->getDeploy_territories().end())
            {
                cout << "Wrong name, please try again." << endl;
                cin >> target_name;
            }
            p->addOrder(new Airlift(this->p, p->getDeploy_territories()[source_name], p->getDeploy_territories()[target_name]));
            p->gethandofcard()->remove_CardinHand_ByType("airlift");
        }
        else if (orderName == "diplomacy")
        {
            cout << "Using diplomacy card" << endl;
            cout << "Please choose a victim" << endl;
            cout << "The available players are: ";
            for (std::map<string, Player *>::iterator it = p->getPlayers_Map().begin(); it != p->getPlayers_Map().end(); ++it)
            {
                cout << it->first << "  ";
            }
            string name;
            cin >> name;
            while (p->getPlayers_Map().find(name) == p->getPlayers_Map().end())
            {
                cout << "No such player, are you kidding me?! Try again";
                cin >> name;
            }
            p->addOrder(new Negotiate(this->p, p->getPlayers_Map()[name]));
            p->gethandofcard()->remove_CardinHand_ByType("diplomacy");
        }
        else if (orderName == "blockade")
        {
            cout << "Using the blockade card, please choose one of your territory" << endl;
            cout << "Available territories are: ";
            for (std::map<string, Territory *>::iterator it = p->getDeploy_territories().begin(); it != p->getDeploy_territories().end(); ++it)
            {

                cout << it->first << "  ";
            }
            string target_name;
            cin >> target_name;
            while (p->getDeploy_territories().find(target_name) == p->getDeploy_territories().end())
            {
                cout << "Wrong name, please try again." << endl;
                cin >> target_name;
            }
            this->p->addOrder(new Blockade(this->p, p->getAvailable_territories()[target_name]));
            this->p->gethandofcard()->remove_CardinHand_ByType("blockade");
        }
    }
}
vector<Territory *> BenevolentPlayerStrategy::toAttack()
{
    // never attack
    cout << "cannot attack,return empty default vector" << endl;
    vector<Territory *> empty;
    return empty;
}
bool BenevolentPlayerStrategy::compareInterval(Territory *k1, Territory *k2)
{
    return (k1->getNumberOfArmies() <= k2->getNumberOfArmies());
}
vector<Territory *> BenevolentPlayerStrategy::toDedend()
{
    vector<Territory *> deplicate = this->p->getTerriotory();
    sort(deplicate.begin(), deplicate.end(), compareInterval); // first is weakest
    return deplicate;
}
// OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO

//-------a---------------------------------------------------

AggressivePlayerStrategy::AggressivePlayerStrategy(Player *player) : PlayerStrategy(player)
{
    strategyName = "Aggressive Player";
}
string AggressivePlayerStrategy::getStrategyName()
{
    return this->strategyName;
}

void AggressivePlayerStrategy::issueOrder(string orderName)
{
    if (orderName == "Deploy" | orderName == "Advance" | orderName == "bomb")
    {
        if (orderName == "Deploy")
        {
            std::cout << "for player " << p->getName() << ",AggressivePlayerStrategy." << endl;
            std::cout << "deploy." << endl;
            if (p->getReinforcement() > 0)
            {
                std::cout << "the pool is " << p->getReinforcement() << endl;
                std::cout << "All goes to strongest country:" << toDedend().at(0)->getName() << endl;
                p->addOrder(new Deploy(p->getReinforcement(), p, toDedend().at(0)));
                p->setReinforcement(0);
                p->gethandofcard()->remove_CardinHand_ByType("Deploy");
            }
        }
        else if (orderName == "Advance")
        {
            cout << "Your territories are: ";
            for (std::map<string, Territory *>::iterator it = p->getDeploy_territories().begin(); it != p->getDeploy_territories().end(); ++it)
            {
                cout << it->first << "  ";
            }
            cout << endl;
            cout << "Choose the source territory: ";
            string source_name;
            cin >> source_name;
            while (p->getDeploy_territories().find(source_name) == p->getDeploy_territories().end())
            {
                cout << "Wrong name, please try again." << endl;
                cin >> source_name;
            }
            if (source_name == toDedend().at(0)->getName())
            {
                cout << "chose the strongest territory as source,can start attack!";
                cout << "Please enter the target territory: " << endl;
                cout << "The available options are  the enemy territories" << endl;
                cout << "Available territories are: ";
                map<string, Territory *> enemy;
                for (std::map<string, Territory *>::iterator it = p->getAvailable_territories().begin(); it != p->getAvailable_territories().end(); ++it)
                {
                    if (!p->ownsTerritory(it->second))
                    {
                        enemy.insert({it->first, it->second});
                        cout << it->first << "  ";
                    } // filter out all own tero
                }
                cout << endl;
                string target_name;
                cin >> target_name;
                while (enemy.find(target_name) == enemy.end())
                {
                    cout << "Wrong name, please try again." << endl;
                    cin >> target_name;
                }
                this->p->addOrder(new Advance(toDedend().at(0), enemy[target_name], p, toDedend().at(0)->getNumberOfArmies()));
            } // else didnt choose the strongest Territory,deploy to strongest
            else
            {
                cout << "didnt choose the strongest Territory,deploy to strongest" << endl;
                this->p->addOrder(new Advance(p->getAvailable_territories()[source_name], toDedend().at(0), this->p, p->getAvailable_territories()[source_name]->getNumberOfArmies()));
            }
        }
        else if (orderName == "bomb")
        {
            cout << "Using the bomb card, please choose a territory" << endl;
            cout << "Available territories are: ";
            for (std::map<string, Territory *>::iterator it = p->getAvailable_territories().begin(); it != p->getAvailable_territories().end(); ++it)
            {

                cout << it->first << "  ";
            }
            string target_name;
            cin >> target_name;
            while (p->getAvailable_territories().find(target_name) == p->getAvailable_territories().end())
            {
                cout << "Wrong name, please try again." << endl;
                cin >> target_name;
            }
            p->addOrder(new Bomb(p, p->getAvailable_territories()[target_name], 0));
            p->gethandofcard()->remove_CardinHand_ByType("bomb");
        }
    }
    else
    {
        if (orderName == "airlift")
        {
            std::cout << "AggressivePlayerStrategy doesnt airlift." << endl;
            p->gethandofcard()->remove_CardinHand_ByType("airlift");
        }
        else if (orderName == "diplomacy")
        {
            std::cout << "AggressivePlayerStrategy doesnt diplomacy." << endl;
            p->gethandofcard()->remove_CardinHand_ByType("diplomacy");
        }
        else if (orderName == "blockade")
        {
            std::cout << "AggressivePlayerStrategy doesnt blockade." << endl;
            p->gethandofcard()->remove_CardinHand_ByType("blockade");
        }
    }
}
bool AggressivePlayerStrategy::compareInterval(Territory *k1, Territory *k2)
{
    return (k1->getNumberOfArmies() >= k2->getNumberOfArmies());
}
vector<Territory *> AggressivePlayerStrategy::toAttack()
{
    vector<Territory *> deplicate = this->p->getTerriotory();
    sort(deplicate.begin(), deplicate.end(), compareInterval); // first is weakest
    return deplicate;
}
vector<Territory *> AggressivePlayerStrategy::toDedend()
{
    cout << "cannot defend,always attack,return empty default vector" << endl;
    vector<Territory *> empty;
    return empty;
}
