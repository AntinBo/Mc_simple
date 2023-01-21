
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
    for (class Player *p : players)
    {
        p->setWorld(nullptr);
    }

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

bool World::loadPlayer(class Player *p_new, class Player *p_old)
{
    for (class Player *p : players)
    {
        if (p == p_old)
        {
            players.remove(p);
            players.push_back(p_new);
            return true;
        }
    }
    return false;
}

void World::load(std::ifstream & f)
{   
    int length;
    char c_name[128];
    class Player *p;

    // Name
    f.read((char *)&length, sizeof(length)); // int
    f.read(c_name, length);
    c_name[length] = '\0';
    name = c_name;

    // Type
    f.read((char *)&type, sizeof(type));
    
    // Pointers of players
    f.read((char *)&length, sizeof(length));
    for (; length > 0; length--)
    {
        f.read((char *)&p, sizeof(p));
        players.push_back(p);
    }
}

void World::save(std::ofstream & f) const
{
    int length;

    // Name
    length = name.length();
    f.write((const char *)&length, sizeof(length)); // int
    f.write(name.c_str(), length); 

    // Type
    f.write((const char *)&type, sizeof(type));

    // Pointers of players
    length = players.size();
    f.write((const char *)&length, sizeof(length));

    for (class Player *p : players)
    {
        f.write((const char *)&p, sizeof(p));
    }
}