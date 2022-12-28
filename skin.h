
#include <iostream>
#include <fstream>
#include <list>

class Skin
{
    public:
        enum Colors
        {
            SC_red,
            SC_yellow,
            SC_green,
            SC_blue
        };

        enum Width
        {
            SW_normal,
            SW_thin
        };

        Skin();
        Skin(Skin::Colors c, Skin::Width w);

        const Skin::Colors & getColor() const;
        const Skin::Width & getWidth() const;

        void load(std::ifstream &f);
        void save(std::ofstream &f) const;

    protected:

    private:
        Colors color;
        Width  width;
};