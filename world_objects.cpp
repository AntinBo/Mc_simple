
#include <iostream>

#include "world_objects.h"

/* ---------- class WorldObject ---------- */
    
WorldObject::WorldObject() : x(0.0), y(0.0)
{
}

void WorldObject::setXY(float pos_x, float pos_y)
{
    x = pos_x;
    y = pos_y;
}
void WorldObject::getXY(float &pos_x, float &pos_y) const
{
    pos_x = x;
    pos_y = y;
}

/* ---------- class Fish ---------- */

Fish::Fish(const std::string &tn)
{
    type_name = tn;
}

const std::string &Fish::getTypeName() const
{
    return type_name;
}

void Fish::load(std::ifstream &f)
{
    f.read((char *)&x, sizeof(x));
    f.read((char *)&y, sizeof(y));
}

void Fish::save(std::ofstream &f) const
{
    f.write((const char *)&x, sizeof(x));
    f.write((const char *)&y, sizeof(y));
}

/* ---------- class Tuna ---------- */

Tuna::Tuna() : Fish(" T ")
{
}

/* ---------- class Carp ---------- */

Carp::Carp() : Fish(" C ")
{  
}