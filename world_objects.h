
#ifndef WORLD_OBJECTS_H
#define WORLD_OBJECTS_H

#include <fstream>
#include <string>

class Fish
{
    public:
        Fish();

        const std::string &getTypeName() const;

        void load(std::ifstream &f);
        void save(std::ofstream &f) const;

        void setXY(float pos_x, float pos_y);
        void getXY(float &pos_x, float &pos_y) const;

    protected:

    private:
        float x, y;
        std::string type_name;
};

class Tuna: public Fish
{
    public:
        Tuna();
};

class Carp: public Fish
{
    public:
        Carp();
};

#endif /* WORLD_OBJECTS_H */