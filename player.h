
#include <string>

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

        Player(unsigned int I, const std::string & n, Skin::Colors c, Skin::Width w);

        const std::string & getNick() const;
        
        void setWorld(class World *w);
        class World *getWorld();

        void showPlayerStatus() const;

    protected:

    private:
        unsigned int Id;     /* uniq identificator */
        std::string  nick;   /* nickname */
        class Skin   skin;   /* skin */            
        unsigned int health; /* health */ 
        State        state;  /* emotion */
        class World *world;
};