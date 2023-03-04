
#ifndef WORLD_H
#define WORLD_H

#include <string>
#include <fstream>
#include <list>

#include "world_objects.h"

class Player;

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
        
        bool joinPlayer(class Player *p);
        bool disjoinPlayer(class Player *p);

        bool loadPlayer(class Player *p_new, class Player *p_old);

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
        std::list<class Player *> players;
        // Add Tuna and Carp - x/y positions(show map, tuna - T, carp - C)
        Tuna myLunch;
        Carp myDinner;
};

#endif /* WORLD_H */