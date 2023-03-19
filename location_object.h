
#ifndef LOCATION_OBJECTS_H
#define LOCATION_OBJECTS_H

#include <fstream>
#include <string>

class LocationObject
{
public:
    LocationObject();
    virtual ~LocationObject();

    void setXY(float pos_x, float pos_y);
    void getXY(float &pos_x, float &pos_y) const;

    virtual const std::string &getTypeName() const = 0; // pure virtual fucntion

protected:
    float x, y;

private:
};

#endif /* LOCATION_OBJECTS_H */