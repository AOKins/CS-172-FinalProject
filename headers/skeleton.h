#ifndef _SKELETON_H_
#define _SKELETON_H_

#include "entity.h"
using namespace std;



class Skeleton : public Entity {
public:
    Skeleton() : Entity() {}
    Skeleton(string set_name, int set_hp, int set_x, int set_y) : Entity( set_name, set_hp, set_x, set_y) {}
  
    void move(string direction);
    void attack();
    void draw();

};

ostream& operator<<(ostream & os, Skeleton * &skeleton);


#endif