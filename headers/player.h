#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "entity.h"
using namespace std;

class Player : public Entity {
private:
  bool key;
public:
    Player() : Entity() {}
    Player(string set_name, int set_hp, int set_x, int set_y) : Entity( set_name, set_hp, set_x, set_y) {}
    bool has_key();
    void move(string direction);
    void attack();
    void draw();
};

ostream& operator<<(ostream & os, Player * &player);

#endif