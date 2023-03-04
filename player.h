
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <fstream>
#include <list>

#include "skin.h"

class World;

class Player
{ 
    public:
        enum State
        {
            PS_happy,
            PS_normal,
            PS_sad,
            PS_none
        };

        Player();
        Player(unsigned int I, const std::string & n, Skin::Colors c, Skin::Width w);
        ~Player();

        const std::string & getNick() const;
        
        void setWorld(class World *w);
        class World *getWorld();

        void showPlayerStatus() const;

        void setXY(float pos_x, float pos_y);
        void getXY(float & pos_x, float & pos_y) const;

        void load(std::ifstream &f, std::list<class World *> & list_worlds);
        void save(std::ofstream &f) const;

        void fishHasCatched();

    protected:

    private:
        unsigned int Id;     /* uniq identificator */ 
        std::string  nick;   /* nickname */
        class Skin   skin;   /* skin */       
        unsigned int health; /* health */               
        State        state;  /* emotion */
        int          fish;   /* amount of catched fish */        
        float        x, y;   /* player's cordinats */
        class World *world;                
};

#endif /* PLAYER_H */