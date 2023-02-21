
#include "world_objects.h"

/* ---------- class Fish ---------- */

Fish::Fish()
{

}

const std::string &Fish::getTypeName() const
{
    return type_name;
}

void Fish::setXY(float pos_x, float pos_y)
{
    x = pos_x;
    y = pos_y;
}

/* ---------- class Tuna ---------- */

Tuna::Tuna()
{
}

/* ---------- class Carp ---------- */

Carp::Carp()
{  
}