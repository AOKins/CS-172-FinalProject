#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "entity.h"

using namespace std;

class Player : public Entity {
private:
  bool key;
public:
    Player() : Entity() {}
    Player(string set_name, int set_hp, Location* set_loc) : Entity(set_name, set_hp, set_loc) {}

    Player(string set_name, int set_hp, Location * set_loc, bool set_key);

    void attack(string direction, vector<Entity*> entities);
    void hurt() {hp -= 1;}
    void move(string direction, vector<Item*> items);
    bool has_key() {return key;}
    void found_key();
};

ostream& operator<<(ostream & os, Player &player);

#endif