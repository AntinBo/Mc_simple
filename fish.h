
#ifndef FISH_H
#define FISH_H

#include <fstream>
#include <string>

#include "location_object.h"

class Fish : public LocationObject
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

#endif /* FISH_H */