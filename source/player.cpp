#include "player.h"
#include <iostream>


Player::Player(string set_name, int set_hp, Location* set_loc, bool set_key){
    name = set_name;
    hp = set_hp;
    loc = set_loc;
    key = set_key;
}


void Player::move(string direction, vector<Item*> items){
    // Go through all of the items, and if one of them is where the player is trying to go to and it is not traversable, then can't move //
    bool can_move = true;
    for (int i = 0; i < items.size(); i++){
      if ( (targeting(direction, *loc) == items[i]->getLOC()) && !items[i]->traversable()) {
          can_move = false;
      }
    }

    if (can_move){
      if (direction == "north"){     loc->MoveUP();}
      else if (direction =="south"){ loc->MoveDOWN();}
      else if (direction == "west"){ loc->MoveLEFT();}
      else if (direction == "east"){ loc->MoveRIGHT();}
    }
    else {cout << name << " hit a wall!\n";}
}

void Player::attack(string direction, vector<Entity*> entities){
    // Skips 0, since that is always the player //
    for (int i = 1; i < entities.size(); i++){
      // If the entity is where the player is targeting, it hurts the entity //
      if ( targeting(direction, *loc) == entities[i]->getLOC() ){
          cout << name << " successfully attacked " << entities[i]->getName() << endl;
          entities[i]->hurt();
            }
        }
}
// Basic function to set the key to true //
void Player::found_key(){
  key = true;
}


// Overloads the << operator for use in saving the game //
ostream & operator<<(ostream & os, Player &player){
  os << "Player "
     << player.getName() << " "
     << player.getHP() << " "
     << player.has_key() << " " 
     << player.getLOC().getLocX() << " " 
     << player.getLOC().getLocY();
  return os;
}