#include "entity.h"

Entity::Entity(){}

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

// Accesses the location of the entity and moves it in the given direction //
void Entity::move(string direction){
    if (direction == "north"){
        loc->MoveUP();
    }
    else if (direction == "south"){
        loc->MoveDOWN();
    }
    else if (direction == "west"){
        loc->MoveLEFT();
    }
    else if (direction == "east"){
        loc->MoveRIGHT();
    }
}