
#include <iostream>
#include <fstream>

#include "location.h"
#include "fisherman.h"
#include "fish.h"

#define SMALL_LOCATION_MAP_SIZE 10

using namespace std;

const char * location_type[] = 
{
    "Lake",
    "River",
    "Sea"
};

const float location_map_size[] =
{
    10.0,
    30.0,
    50.0
};

Location::Location()
{
    fish[0] = new Tuna();
    fish[1] = new Carp();
}

Location::Location(string n, LocationType t)
{
    name = n;

    if (t >= LT_Count)
        type = LT_Lake;
    else
        type = t;

    cout << "Location was created(" << name << ", type: " << getLocationType() << ")" << endl;

    fish[0] = new Tuna();
    fish[1] = new Carp();
}

Location::~Location()
{
    for (class Fisherman *p : fishermen)
    {
        p->setLocation(nullptr);
    }

    cout << "Location was deleted(" << name << ", " << getLocationType() << ")" << endl;
}

const string &Location::getName() const
{
    return name;
}

const char * Location::getLocationType() const
{
    return location_type[type];
}

void Location::showLocationStatus() const
{
    int n = 1;

    cout << "Location(" << name << ", type: " << getLocationType() << ")" << endl;
    cout << "  Fishermen:" << endl;
    cout << "  --------" << endl;
    for (class Fisherman *p : fishermen)
    {
        cout << "  " << n++ << ". " << p->getNick() << endl;
    }
}

float Location::getMaxMapSize() const
{
    return location_map_size[type];
}

void Location::showMap() const
{
    int index;
    float x, y;
    bool empty_cell;
    float cur_x, cur_y;
    if (location_type[0])
    {
        cout << "Location(" << name << ", type: " << getLocationType() << ")" << endl;
        cout << "+ 0  1  2  3  4  5  6  7  8  9 +" << endl;
        for (cur_y = 0; cur_y < getMaxMapSize(); cur_y++)
        {
            cout << cur_y;

            for (cur_x = 0; cur_x < getMaxMapSize(); cur_x++)
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

                // Search fisherman's in position X, Y
                for (class Fisherman *p : fishermen)
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
}

bool Location::joinFisherman(class Fisherman *p)
{
    class Location *w;

    w = p->getLocation();

    if (w == nullptr)
    {
        fishermen.push_back(p);
        p->setLocation(this);
        
        return true;
    }

    return false;                             
}

bool Location::disjoinFisherman(class Fisherman *p)
{
    fishermen.remove(p);    

    return true;   
}

bool Location::loadFisherman(class Fisherman *p_new, class Fisherman *p_old)
{
    for (class Fisherman *p : fishermen)
    {
        if (p == p_old)
        {
            fishermen.remove(p);
            fishermen.push_back(p_new);
            return true;
        }
    }
    return false;
}

void Location::load(std::ifstream & f)
{   
    int index;
    int length;
    char c_name[128];
    class Fisherman *p;

    // Name
    f.read((char *)&length, sizeof(length)); // int
    f.read(c_name, length);
    c_name[length] = '\0';
    name = c_name;

    // Type
    f.read((char *)&type, sizeof(type));
    
    // Pointers of fishermen
    f.read((char *)&length, sizeof(length));
    for (; length > 0; length--)
    {
        f.read((char *)&p, sizeof(p));
        fishermen.push_back(p);
    }

    for (index = 0; index < FISH_COUNT; index++)
        fish[index]->load(f);
}

void Location::save(std::ofstream & f) const
{
    int index;
    int length;

    // Name
    length = name.length();
    f.write((const char *)&length, sizeof(length)); // int
    f.write(name.c_str(), length); 

    // Type
    f.write((const char *)&type, sizeof(type));

    // Pointers of fishermen
    length = fishermen.size();
    f.write((const char *)&length, sizeof(length));

    for (class Fisherman *p : fishermen)
    {
        f.write((const char *)&p, sizeof(p));
    }

    for (index = 0; index < FISH_COUNT; index++)
        fish[index]->save(f);
}

void Location::setTunaXY(float pos_x, float pos_y)
{
    fish[0]->setXY(pos_x, pos_y);
}
// void getTunaXY(float &pos_x, float &pos_y) const
void Location::setCarpXY(float pos_x, float pos_y)
{
    fish[1]->setXY(pos_x, pos_y);
}
// void getCarpXY(float &pos_x, float &pos_y) const

void Location::playRound()
{
    float x, y;
    float cur_x_tuna, cur_y_tuna, cur_x_carp, cur_y_carp;

    // Get random X and Y for Tuna and set new position for Tuna
    cur_x_tuna = rand() % ((int)Location::getMaxMapSize());
    cur_y_tuna = rand() % ((int)Location::getMaxMapSize());
    setTunaXY(cur_x_tuna, cur_y_tuna);

    // Get random X and Y for Carp and set new position for Carp
    cur_x_carp = rand() % ((int)Location::getMaxMapSize());
    cur_y_carp = rand() % ((int)Location::getMaxMapSize());
    setCarpXY(cur_x_carp, cur_y_carp);

    fish[0]->getXY(cur_x_tuna, cur_y_tuna);
    fish[1]->getXY(cur_x_carp, cur_y_carp);

    // Reckon of points to fisherman
    for (class Fisherman *p : fishermen)
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