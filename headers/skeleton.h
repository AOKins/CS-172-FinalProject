#ifndef _SKELETON_H_
#define _SKELETON_H_

#include "entity.h"
#include "player.h"
using namespace std;



class Skeleton : public Entity {
public:
    Skeleton() : Entity() {}
    Skeleton(string set_name, int set_hp, Location* set_loc) : Entity(set_name, set_hp, set_loc) {}

    void attack(Player* player);
    void hurt() {hp -= 1;}
    void move(string direction, vector<Item*> items);

    bool CanMove(string direction, vector<Item*> items);
};

ostream& operator<<(ostream & os, Skeleton &skeleton);


#endif