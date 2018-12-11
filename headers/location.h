#ifndef _LOCATION_H_
#define _LOCATION_H_
#include <iostream>
using namespace std;

class Location{
private:
    int x,y;
public:
    Location();
    Location(int start_x, int start_y);
    int getLocX();
    int getLocY();

    void MoveUP();
    void MoveDOWN();
    void MoveLEFT();
    void MoveRIGHT();

    bool operator==(Location other_loc);
    void operator=(Location other_loc);

};

ostream& operator<<(ostream & os, Location loc);

#endif