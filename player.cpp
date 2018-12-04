#include "player.h"
#include <iostream>

void Player::move(string direction){
    if (direction == "north"){
        loc->MoveUP();
        Player::draw();
    }
    else if (direction == "south"){
        loc->MoveDOWN();
        Player::draw();
    }
    else if (direction == "west"){
        loc->MoveLEFT();
        Player::draw();
    }
    else if (direction == "east"){
        loc->MoveRIGHT();
        Player::draw();
    }
}

void Player::attack(){
    cout << "You lash out into the darkness, but you hit nothing\n";
}

bool Player::has_key(){
  return key;
}

void Player::draw(){
  Entity::draw();
  cout << "P";
}


ostream & operator<<(ostream & os, Player* &player){
  os << "Player ";
  os << player->getName() << " "
     << player->getHP() << " "
     << player->has_key() << " ";
  
     Location temp = player->getLOC();
      int x = temp.getLocX();
      int y = temp.getLocY();
  os  << x << " " << y;
  return os;
}