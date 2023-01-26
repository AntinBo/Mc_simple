
#include <iostream>

#include "player.h"
#include "world.h"

using namespace std;

Player::Player() : 
    x(0.0), y(0.0)
{

}

Player::Player(unsigned int _Id, const string & _nick, Skin::Colors c, Skin::Width w) :
    Id(_Id), nick(_nick), skin(c, w), health(100), state(PS_happy), x(0.0), y(0.0), world(nullptr)
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
    cout << "  Player(" << Id << ", " << nick << ", " << (int) skin.getColor()
        << ", " << (int) skin.getWidth() << ", " << health << ", " << state << ")" << endl;
    if (world != nullptr)
    {
        cout << "    World: " << world->getName() << endl;
    }
}

void Player::setXY(float pos_x, float pos_y)
{
    x = pos_x;
    y = pos_y;
}

void Player::getXY(float & pos_x, float & pos_y) const
{
    pos_x = x;
    pos_y = y;
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

    // 6 - Loadnig old self-pointer
    f.read((char *)&p, sizeof(p));
    for (class World *w : list_worlds)
    {   
        if (w->loadPlayer(this, p))
        {
            world = w;
            break;
        }
    }
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

    // 6 - Saving self-pointer
    p = this;
    f.write((const char *)&p, sizeof(p));
}