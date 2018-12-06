#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <string>
#include <vector>
#include "location.h"

using namespace std;

class Entity{
protected:
    string name;
    int hp;
    Location * loc;
public:
    Entity();
    Entity(string set_name, int set_hp, int set_x, int set_y);

    string getName();
    int getHP();
    void move(string direction);
    void virtual hurt() = 0;

    Location getLOC();
};

#endif