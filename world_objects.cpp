
#include <iostream>

#include "world_objects.h"

/* ---------- class Fish ---------- */

Fish::Fish()
{

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

void Fish::setXY(float pos_x, float pos_y)
{
    x = pos_x;
    y = pos_y;
}

void Fish::getXY(float &pos_x, float &pos_y) const
{
    pos_x = x;
    pos_y = y;
}

/* ---------- class Tuna ---------- */

Tuna::Tuna()
{
}

/* ---------- class Carp ---------- */

Carp::Carp()
{  
}