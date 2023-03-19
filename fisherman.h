
#ifndef FISHERMAN_H
#define FISHERMAN_H

#include <string>
#include <fstream>
#include <list>

#include "skin.h"
#include "world_objects.h"

class World;

class Fisherman : public WorldObject
{ 
    public:
        enum State
        {
            PS_happy,
            PS_normal,
            PS_sad,
            PS_none
        };

        Fisherman();
        Fisherman(unsigned int I, const std::string &n, Skin::Colors c, Skin::Width w);
        ~Fisherman();

        const std::string & getNick() const;
        
        void setWorld(class World *w);
        class World *getWorld();

        void showFishermanStatus() const;

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

#endif /* FISHERMAN_H */