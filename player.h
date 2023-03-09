
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <fstream>
#include <list>

#include "skin.h"
#include "world_objects.h"

class World;

class Player : public WorldObject
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

        void load(std::ifstream &f, std::list<class World *> & list_worlds);
        void save(std::ofstream &f) const;

        void fishHasCatched();
        void showFish();

        virtual const std::string &getTypeName() const;

    protected:

    private: 
        unsigned int Id; /* uniq identificator */
        std::string  nick;   /* nickname */
        class Skin   skin;   /* skin */       
        unsigned int health; /* health */               
        State        state;  /* emotion */
        int          fish;   /* amount of catched fish */        
        class World *world;                
};

#endif /* PLAYER_H */