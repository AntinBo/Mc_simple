
#include <vector>
#include <iostream>
#include <fstream>
#include <stdarg.h>

#include "location.h"
#include "fisherman.h"
#include "fish.h"

#define SMALL_LOCATION_MAP_SIZE 10

using namespace std;

struct arrayStructure
{
    const char * type_name;
    float map_size;
};

struct arrayStructure actualArray[Location::LT_Count] = {
    {"Lake", 10.0},
    {"River", 30.0},
    {"Sea", 50.0}
};

std::string format(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    std::vector<char> v(1024);
    while (true)
    {
        va_list args2;
        va_copy(args2, args);
        int res = vsnprintf(v.data(), v.size(), fmt, args2);
        if ((res >= 0) && (res < static_cast<int>(v.size())))
        {
            va_end(args);
            va_end(args2);
            return std::string(v.data());
        }
        size_t size;
        if (res < 0)
            size = v.size() * 2;
        else
            size = static_cast<size_t>(res) + 1;
        v.clear();
        v.resize(size);
        va_end(args2);
    }
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
    return actualArray[type].type_name;
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
    return actualArray[type].map_size;
}

void Location::showMap() const
{
    int n;
    int index;
    float x, y;
    std::string str;
    float cur_x, cur_y;
    const class Fisherman *p;
    std::list<class Fisherman *>::const_iterator ci;

    cout << "Location(" << name << ", type: " << getLocationType() << ")" << endl;
    cout << " + ";
    for (n = 0; n < (int)getMaxMapSize(); n++)
    {
        str = format("%3d", n);
        cout << str;
    };
    cout << " +" << endl;
    
    for (cur_y = 0; cur_y < getMaxMapSize(); cur_y++)
    {
        str = format("%2d ", ((int)cur_y));
        cout << str;

        for (cur_x = 0; cur_x < getMaxMapSize(); cur_x++)
        {
            for (index = 0; index < FISH_COUNT; index++)
            {
                fish[index]->getXY(x, y);
                if (cur_x == x && cur_y == y)
                {
                    cout << fish[index]->getTypeName();
                }
                else
                {
                    cout << " ";
                }
            }

            // Search fisherman's in position X, Y
            for (ci = fishermen.cbegin(); ci != fishermen.cend(); ++ci)
            {
                p = (*ci);
                //(*ci)->getXY(x, y);
                p->getXY(x, y);
                if (cur_x == x && cur_y == y)
                {
                    cout << p->getTypeName();
                    break;
                }
            }

            if (ci == fishermen.cend())
                cout << "-";
        }

        cout << " |" << endl;
    }

    cout << " + ";
    for (n = 0; n < (int)getMaxMapSize(); n++)
    {
        //str = format("%3d", n);
        cout << "---";
    };
    cout << " +" << endl;
}

bool Location::isSpotEmpty(float x, float y)
{
    bool empty;
    float cur_x, cur_y;
    
    // Checking if coordinates for all the fishermen are different
    empty = true;

    for (class Fisherman *fm : fishermen)
    {
        fm->getXY(cur_x, cur_y);
        if (cur_x == x && cur_y == y)
        {
            empty = false;
            break;
        }
    }

    return empty;
}

bool Location::joinFisherman(class Fisherman *p)
{
    float x, y;

    p->getXY(x, y);

    if (isSpotEmpty(x, y))
    {
        fishermen.push_back(p);
        p->setLocation(this);
        cout << "Fisherman has been added successfully" << endl;
        return true;
    }
    else
    {
        cout << "You can't join another fisherman to this spot. Change coordinates for him first" << endl;
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