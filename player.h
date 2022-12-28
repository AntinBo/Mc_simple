
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

        const std::string & getNick() const;
        
        void setWorld(class World *w);
        class World *getWorld();

        void showPlayerStatus() const;

        void load(std::ifstream &f, std::list<class World *> & list_worlds);
        void save(std::ofstream &f) const;

    protected:

    private:
        unsigned int Id;     /* uniq identificator */ 
        std::string  nick;   /* nickname */
        class Skin   skin;   /* skin */    // Create funcs save and load for this class          
        unsigned int health; /* health */  // int
        State        state;  /* emotion */ // int
        class World *world;                
};