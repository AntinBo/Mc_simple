
#include <string>
#include <fstream>
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

        World();
        World(std::string n, Type t);
        ~World();

        const std::string & getName() const;
        bool addPlayer(class Player *p);
        bool deletePlayer(class Player *p);
        bool loadPlayer(class Player *p_new, class Player *p_old);
        void showWorldStatus() const;

        void load(std::ifstream & f);
        void save(std::ofstream & f) const;

    protected:

    private:
        std::string name;
        Type type;
        std::list<class Player*> players;
};