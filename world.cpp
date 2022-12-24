
#include <iostream>
#include <fstream>

#include "world.h"
#include "player.h"

using namespace std;

World::World()
{

}

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

void World::load(std::ifstream & f)
{   
    int length;
    char c_name[128];

    f.read((char *)&length, sizeof(length)); // int
    f.read(c_name, length);
    f.read((char *)&type, sizeof(type));
    
    c_name[length] = '\0';
    name = c_name;
}

void World::save(std::ofstream & f) const
{
    int length;

    length = name.length();

    f.write((const char *)&length, sizeof(length)); // int
    f.write(name.c_str(), length); 
    f.write((const char *)&type, sizeof(type));
}