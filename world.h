
#include <string>
#include <list>

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

        World(std::string n, Type t);
        ~World();

        const std::string & getName() const;
        bool addPlayer(class Player *p);
        bool deletePlayer(class Player *p);
        void showWorldStatus() const;

    protected:

    private:
        std::string name;
        Type type;
        std::list<class Player*> players;
};