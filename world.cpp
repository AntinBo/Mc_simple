
#include <iostream>
#include <fstream>

#include "world.h"
#include "player.h"
#include "world_objects.h"

#define WORLD_MAP_SIZE 10

using namespace std;

World::World()
{
    fish[0] = new Tuna();
    fish[1] = new Carp();
}

World::World(string n, Type t)
{
    name = n;
    type = t;

    cout << "World was created(" << name << ", " << type << ")" << endl;

    fish[0] = new Tuna();
    fish[1] = new Carp();
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
        cout << "  " << n++ << ". " << p->getNick() << endl;
    }
}

void World::showMap() const
{
    int index;
    float x, y;
    bool empty_cell;
    float cur_x, cur_y;

    cout << "World(" << name << ", " << type << ")" << endl;
    cout << "+ 0  1  2  3  4  5  6  7  8  9 +" << endl;
    for (cur_y = 0; cur_y < WORLD_MAP_SIZE; cur_y++)
    {
        cout << cur_y;

        for (cur_x = 0; cur_x < WORLD_MAP_SIZE; cur_x++)
        {

            empty_cell = true;

            for (index = 0; index < FISH_COUNT; index++)
            {
                fish[index]->getXY(x, y);
                if (cur_x == x && cur_y == y)
                {
                    cout << fish[index]->getTypeName();
                    empty_cell = false;
                }
            }

            // Search players in position X, Y
            for (class Player *p : players)
            {
                p->getXY(x, y);
                if (cur_x == x && cur_y == y)
                {
                    if (empty_cell)
                    {
                        cout << p->getTypeName();
                        empty_cell = false;
                    }
                }
            }

            if (empty_cell)
                cout << " - ";
        }

        cout << "|" << endl;
    }                                       
    cout << "+------------------------------+" << endl;
}

float World::getMaxMapSize()
{
    return WORLD_MAP_SIZE;
}

const string & World::getName() const
{
    return name;
}

bool World::joinPlayer(class Player *p)
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

bool World::disjoinPlayer(class Player *p)
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
    int index;
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

    for (index = 0; index < FISH_COUNT; index++)
        fish[index]->load(f);
}

void World::save(std::ofstream & f) const
{
    int index;
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

    for (index = 0; index < FISH_COUNT; index++)
        fish[index]->save(f);
}

void World::setTunaXY(float pos_x, float pos_y)
{
    fish[0]->setXY(pos_x, pos_y);
}
// void getTunaXY(float &pos_x, float &pos_y) const
void World::setCarpXY(float pos_x, float pos_y)
{
    fish[1]->setXY(pos_x, pos_y);
}
// void getCarpXY(float &pos_x, float &pos_y) const

void World::playRound()
{
    float x, y;
    float cur_x_tuna, cur_y_tuna, cur_x_carp, cur_y_carp;

    // Get random X and Y for Tuna and set new position for Tuna
    cur_x_tuna = rand() % ((int)World::getMaxMapSize());
    cur_y_tuna = rand() % ((int)World::getMaxMapSize());
    setTunaXY(cur_x_tuna, cur_y_tuna);

    // Get random X and Y for Carp and set new position for Carp
    cur_x_carp = rand() % ((int)World::getMaxMapSize());
    cur_y_carp = rand() % ((int)World::getMaxMapSize());
    setCarpXY(cur_x_carp, cur_y_carp);

    fish[0]->getXY(cur_x_tuna, cur_y_tuna);
    fish[1]->getXY(cur_x_carp, cur_y_carp);

    // Reckon of points to player
    for (class Player *p : players)
    {
        p->getXY(x, y); 

        // Catch Tuna
        if (cur_x_tuna == x && cur_y_tuna == y)
        {
            p->fishHasCatched();
        }

        // Catch Carp
        if (cur_x_carp == x && cur_y_carp == y)
        {
            p->fishHasCatched();
        }
    }
}