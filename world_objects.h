
#ifndef WORLD_OBJECTS_H
#define WORLD_OBJECTS_H

#include <fstream>
#include <string>

class WorldObject
{
    public:
        WorldObject();
        virtual ~WorldObject();

        void setXY(float pos_x, float pos_y);
        void getXY(float &pos_x, float &pos_y) const;

        virtual const std::string &getTypeName() const = 0; // pure virtual fucntion

    protected:
        float x, y;

    private:
};

class Fish : public WorldObject
{
    public:
        Fish();

        void load(std::ifstream &f);
        void save(std::ofstream &f) const;

    protected:
    private:
};

class Tuna: public Fish
{
    public:
        Tuna();

        virtual const std::string &getTypeName() const;
};

class Carp: public Fish
{
    public:
        Carp();

        virtual const std::string &getTypeName() const;
};

#endif /* WORLD_OBJECTS_H */