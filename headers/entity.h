#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <string>
#include <vector>
#include "location.h"
#include "item.h"

using namespace std;

class Entity{
protected:
    string name;
    int hp;
    Location * loc;
public:
    Entity();
    Entity(string set_name, int set_hp, Location* set_loc);

    string getName();
    int getHP();
    Location targeting(string direction, Location start);
    Location getLOC();

    void virtual move(string direction, vector<Item*> items) = 0;
    void virtual hurt() = 0;
};

#endif