#include "entity.h"

Entity::Entity(){}

Entity::Entity(string set_name, int set_hp, Location* set_loc) {
    name = set_name;
    hp = set_hp;
    loc = set_loc;
}

// For things such as movement and attacking, where knowing the location of what is ahead is important //
Location Entity::targeting(string direction, Location start){
    if (direction == "north")
        return Location(start.getLocX(),start.getLocY()+1);
    else if (direction == "south")
        return Location(start.getLocX(),start.getLocY()-1);
    else if (direction == "west")
        return Location(start.getLocX()-1,start.getLocY());
    else if (direction == "east")
        return Location(start.getLocX()+1,start.getLocY());
    else {
      return start;
    }
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