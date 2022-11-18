
#include <iostream>

#include "world.h"
#include "player.h"

using namespace std;

World::World(string n, Type t)
{
    name = n;
    type = t;

    cout << "World was created(" << name << ", " << type << ")" << endl;
}

World::~World()
{
    cout << "World was deleted(" << name << ", " << type << ")" << endl;
}

void World::showWorldStatus() const
{
    int n = 1;

    cout << "World(" << name << ", " << type << ")" << endl;
    cout << "  Players:" << endl;
    cout << "  --------" << endl;
    for (class Player *p : players)
    {
        cout << "  " << n << ". " << p->getNick() << endl;
    }
}

const string & World::getName() const
{
    return name;
}

bool World::addPlayer(class Player *p)
{
    class World *w;

    w = p->getWorld();

    if (w == nullptr)
    {
        players.push_back(p); 
        p->setWorld(this);
        
        return true;
    }

    return false;                             
}

bool World::deletePlayer(class Player *p)
{
    players.remove(p);    

    return true;   
}