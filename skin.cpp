
#include <iostream>

#include "skin.h"

using namespace std;

Skin::Skin(Skin::Colors c, Skin::Width w)
{
    color = c;
    width = w;

    cout << "Class Skin was created(" << color << ", " << width << ")" << endl;
}

const Skin::Colors & Skin::getColor() const
{
    return color;
}

const Skin::Width & Skin::getWidth() const
{
    return width;
}