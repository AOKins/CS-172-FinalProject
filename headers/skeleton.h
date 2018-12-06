#ifndef _SKELETON_H_
#define _SKELETON_H_

#include "entity.h"
#include "player.h"
using namespace std;



class Skeleton : public Entity {
public:
    Skeleton() : Entity() {}
    Skeleton(string set_name, int set_hp, int set_x, int set_y) : Entity(set_name, set_hp, set_x, set_y) {}

    void attack(Player* player);
    void hurt() {hp -= 1;}
};

ostream& operator<<(ostream & os, Skeleton &skeleton);


#endif