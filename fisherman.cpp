
#include <iostream>

#include "fisherman.h"
#include "location.h"

using namespace std;

const std::string typeNameFisherman = "*";

Fisherman::Fisherman()
{
}

Fisherman::Fisherman(unsigned int _Id, const string &_nick, Skin::Colors c, Skin::Width w) : Id(_Id), nick(_nick), skin(c, w), health(100), state(PS_happy), fish(0), location(nullptr)
{
    cout << "Fisherman was created(" << Id << ", " << nick << ", " << (int)skin.getColor()
         << ", " << (int)skin.getWidth() << ", " << health << ", " << state << ")" << endl;
}

Fisherman::~Fisherman()
{
    if (location != nullptr)
    {
        location->disjoinFisherman(this);
    }
}

const string &Fisherman::getNick() const
{
    return nick;
}

void Fisherman::setLocation(class Location *w)
{
    location = w;
}

class Location *Fisherman::getLocation()
{
    return location;
}

void Fisherman::showFishermanStatus() const
{
    cout << "  Fisherman(" << Id << ", " << nick << ", " << (int)skin.getColor()
         << ", " << (int)skin.getWidth() << ", " << health << ", " << state << ", f: " << fish << ", x: " << x << ", y: " << y << ")" << endl;
    if (location != nullptr)
    {
        cout << "    Location: " << location->getName() << endl;
    }
}

void Fisherman::load(std::ifstream &f, std::list<class Location *> &list_locations)
{
    int length;
    char c_nick[128];
    class Fisherman *p;

    // 1 - Loading Id
    f.read((char *)&Id, sizeof(Id)); // int

    // 2 - Loading Nick
    f.read((char *)&length, sizeof(length)); // int + str
    f.read(c_nick, length);

    c_nick[length] = '\0';
    nick = c_nick;

    // 3 - Loading skin
    skin.load(f);

    // 4 - Loading health
    f.read((char *)&health, sizeof(health));

    // 5 - Loading state
    f.read((char *)&state, sizeof(state));

    // 6 - Loading x
    f.read((char *)&x, sizeof(x));

    // 7 - Loading y
    f.read((char *)&y, sizeof(y));

    // 8 - Loadnig old self-pointer
    f.read((char *)&p, sizeof(p));
    for (class Location *w : list_locations)
    {
        if (w->loadFisherman(this, p))
        {
            location = w;
            break;
        }
    }

    // 9 - Loading Fish
    f.read((char *)&fish, sizeof(fish));
}

void Fisherman::save(std::ofstream &f) const
{
    int length;
    const class Fisherman *p;

    // 1 - Saving Id
    f.write((const char *)&Id, sizeof(Id));

    // 2 - Saving nick
    length = nick.length();

    f.write((const char *)&length, sizeof(length));
    f.write(nick.c_str(), length);

    // 3 - Saving skin
    skin.save(f);

    // 4 - Saving health
    f.write((const char *)&health, sizeof(health));

    // 5 - Saving state
    f.write((const char *)&state, sizeof(state));

    // 6 - Saving x
    f.write((const char *)&x, sizeof(x));

    // 7 - Saving y
    f.write((const char *)&y, sizeof(y));

    // 8 - Saving self-pointer
    p = this;
    f.write((const char *)&p, sizeof(p));

    // 9 - Saving Fish
    f.write((const char *)&fish, sizeof(fish));
}

void Fisherman::fishHasCatched()
{
    fish++;
}

void Fisherman::showFish()
{
    cout << "f: " << fish << endl;
}

const std::string &Fisherman::getTypeName() const
{
    return typeNameFisherman;
}