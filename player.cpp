
#include <iostream>

#include "player.h"
#include "world.h"

using namespace std;

Player::Player(unsigned int _Id, const string & _nick, Skin::Colors c, Skin::Width w) :
    Id(_Id), nick(_nick), skin(c, w), health(100), state(PS_happy), world(nullptr)
{
    cout << "Player was created(" << Id << ", " << nick << ", " << (int) skin.getColor()
        << ", " << (int) skin.getWidth() << ", " << health << ", " << state << ")" << endl;
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