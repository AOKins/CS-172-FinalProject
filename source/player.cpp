#include "player.h"
#include <iostream>


Player::Player(string set_name, int set_hp, int set_x, int set_y, bool set_key){
    name = set_name;
    hp = set_hp;
    loc = new Location( set_x, set_y );
    key = set_key;
}

// A function that determines if the player is next to the entity by one//
bool at(Location ploc, Location eloc){
    if ( ploc == eloc ){
        return true;
    }
    else {return false;}
}

Location targeting(string direction, Location start){
    if (direction == "north")
        return Location(start.getLocX(),start.getLocY()+1);
    else if (direction == "south")
        return Location(start.getLocX(),start.getLocY()-1);
    else if (direction == "west")
        return Location(start.getLocX()-1,start.getLocY());
    else if (direction == "north")
        return Location(start.getLocX()+1,start.getLocY());
}


void Player::attack(string direction, vector<Entity*> entities){
    int chance = rand() % 2;
    if (chance == 1){
        cout << "You lash out into the darkness, but you hit nothing\n";
    }
    else {
        // Skips 0, since that is always the player //
        for (int i = 1; i < entities.size(); i++){
            
            // If the entity is where the player is targeting, it hurts the entity //
            if ( at( targeting(direction, *loc), entities[0]->getLOC() ) ){
                cout << name << " successfully attacked " << entities[i]->getName() << endl;
                entities[i]->hurt();
            }
        }
    }
}

ostream & operator<<(ostream & os, Player &player){
  os << "Player ";
  os << player.getName() << " "
     << player.getHP() << " "
     << player.has_key() << " ";
  
     Location temp = player.getLOC();
      int x = temp.getLocX();
      int y = temp.getLocY();
  os  << x << " " << y;
  return os;
}