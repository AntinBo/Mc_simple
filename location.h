
#ifndef LOCATION_H
#define LOCATION_H

#include <string>
#include <fstream>
#include <list>

#include "fish.h"

#define FISH_COUNT 2

class Fisherman;

class Location
{
    public:
        enum LocationType
        {
            LT_Lake = 0,
            LT_River,
            LT_Sea,
            
            LT_Count
        };

        Location();
        Location(std::string n, LocationType t);
        ~Location();

        const std::string & getName() const;
        const char * getLocationType() const;

        bool isSpotEmpty(float x, float y);

        bool joinFisherman(class Fisherman *p);
        bool disjoinFisherman(class Fisherman *p);

        bool loadFisherman(class Fisherman *p_new, class Fisherman *p_old);

        void showLocationStatus() const;
        void showMap() const;
        float getMaxMapSize() const;

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
        LocationType type;
        std::list<class Fisherman *> fishermen;
        Fish * fish[FISH_COUNT];
};

#endif /* LOCATION_H */