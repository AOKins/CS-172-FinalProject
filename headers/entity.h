#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <string>
#include <vector>
#include <windows.h>
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

    void virtual attack() = 0;
    string getName();
    int getHP();

    Location getLOC();

    void virtual draw() {
//      SetConsoleCursorPosition(hStdout,loc);
    }

};

#endif