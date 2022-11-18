
#include <iostream>

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

        Skin(Skin::Colors c, Skin::Width w);

        const Skin::Colors & getColor() const;
        const Skin::Width & getWidth() const;

    protected:

    private:
        Colors color;
        Width  width;
};