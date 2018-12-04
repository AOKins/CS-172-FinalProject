#include "entity.h"


Entity::Entity(string set_name, int set_hp, int set_x, int set_y) {
    name = set_name;
    hp = set_hp;
    loc = new Location(set_x, set_y);
}

string Entity::getName() {
    return name;
}

int Entity::getHP() {
    return hp;
}

Location Entity::getLOC(){
  return *loc;
}