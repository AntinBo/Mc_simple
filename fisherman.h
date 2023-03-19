
#ifndef FISHERMAN_H
#define FISHERMAN_H

#include <string>
#include <fstream>
#include <list>

#include "skin.h"
#include "location_object.h"

class Location;

class Fisherman : public LocationObject
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
        
        void setLocation(class Location *w);
        class Location *getLocation();

        void showFishermanStatus() const;

        void load(std::ifstream &f, std::list<class Location *> & list_locations);
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
        class Location *location;                
};

#endif /* FISHERMAN_H */