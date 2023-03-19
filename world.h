
#ifndef WORLD_H
#define WORLD_H

#include <string>
#include <fstream>
#include <list>

#include "world_objects.h"

#define FISH_COUNT 2

class Fisherman;

class World
{
    public:
        enum Type
        {
            WT_normal,
            WT_extended,
            WT_one_biom
        };

        World();
        World(std::string n, Type t);
        ~World();

        const std::string & getName() const;

        bool joinFisherman(class Fisherman *p);
        bool disjoinFisherman(class Fisherman *p);

        bool loadFisherman(class Fisherman *p_new, class Fisherman *p_old);

        void showWorldStatus() const;
        void showMap() const;
        static float getMaxMapSize();

        void load(std::ifstream &f);
        void save(std::ofstream & f) const;

        void setTunaXY(float pos_x, float pos_y);
        // void getTunaXY(float &pos_x, float &pos_y) const;
        void setCarpXY(float pos_x, float pos_y);
        // void getCarpXY(float &pos_x, float &pos_y) const;

        void playRound();

    protected:

    private:
        std::string name;
        Type type;
        std::list<class Fisherman *> fishermen;
        Fish * fish[FISH_COUNT];
};

#endif /* WORLD_H */