
#ifndef WORLD_OBJECTS_H
#define WORLD_OBJECTS_H

#include <fstream>
#include <string>

class WorldObject
{
    public:
        WorldObject();

        void setXY(float pos_x, float pos_y);
        void getXY(float &pos_x, float &pos_y) const;

    protected:
        float x, y;

    private:
};

class Fish : public WorldObject
{
    public:
        Fish(const std::string & tn);

        const std::string &getTypeName() const;

        void load(std::ifstream &f);
        void save(std::ofstream &f) const;

    protected:

    private:
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