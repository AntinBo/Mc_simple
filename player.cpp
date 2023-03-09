
#include <iostream>

#include "player.h"
#include "world.h"

using namespace std;

const std::string typeNamePlayer = " * ";

Player::Player()
{
}

Player::Player(unsigned int _Id, const string &_nick, Skin::Colors c, Skin::Width w) :
    Id(_Id), nick(_nick), skin(c, w), health(100), state(PS_happy), fish(0), world(nullptr)
{
    cout << "Player was created(" << Id << ", " << nick << ", " << (int) skin.getColor()
        << ", " << (int) skin.getWidth() << ", " << health << ", " << state << ")" << endl;
}

Player::~Player()
{
    if (world != nullptr)
    {
        world->joinPlayer(this);
    }
}

const string & Player::getNick() const
{
    return nick;
}

void Player::setWorld(class World *w)
{
    world = w;
}

class World *Player::getWorld()
{
    return world;
}

void Player::showPlayerStatus() const
{
    cout << "  Player(" << Id << ", " << nick << ", " << (int)skin.getColor()
         << ", " << (int)skin.getWidth() << ", " << health << ", " << state << ", f: " << fish << ", x: " << x << ", y: " << y << ")" << endl;
    if (world != nullptr)
    {
        cout << "    World: " << world->getName() << endl;
    }
} 

void Player::load(std::ifstream &f, std::list<class World *> &list_worlds)
{
    int length;
    char c_nick[128];
    class Player * p;

    // 1 - Loadnig Id
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
    for (class World *w : list_worlds)
    {   
        if (w->loadPlayer(this, p))
        {
            world = w;
            break;
        }
    }

    // 9 - Loading Fish
    f.read((char *)&fish, sizeof(fish));
}

void Player::save(std::ofstream &f) const
{
    int length;
    const class Player *p;

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

void Player::fishHasCatched()
{
    fish++;
}

void Player::showFish()
{
    cout << "f: " << fish << endl;
}

const std::string & Player::getTypeName() const
{
    return typeNamePlayer;
}