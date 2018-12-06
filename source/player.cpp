#include "player.h"
#include <iostream>


Player::Player(string set_name, int set_hp, int set_x, int set_y, bool set_key){
    name = set_name;
    hp = set_hp;
    loc = new Location( set_x, set_y );
    key = set_key;
}

void Player::attack(){
    cout << "You lash out into the darkness, but you hit nothing\n";
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