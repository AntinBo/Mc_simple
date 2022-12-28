
#include <iostream>
#include <fstream>
#include <list>

#include "skin.h"

using namespace std;

Skin::Skin()
{
    
}

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

void Skin::load(std::ifstream &f)
{
    // 1 - Loadnig color
    f.read((char *)&color, sizeof(color));

    // 2 - Loadnig width
    f.read((char *)&width, sizeof(width));
}

void Skin::save(std::ofstream &f) const
{
    // 1 - Saving color
    f.write((const char *)&color, sizeof(color));

    // 2 - Saving width
    f.write((const char *)&width, sizeof(width));
}