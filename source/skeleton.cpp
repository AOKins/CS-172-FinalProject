#include "skeleton.h"
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <ctime>

void Skeleton::attack(Player* player){
  srand (time(NULL));

  Location p_L = player->getLOC();
  int p_x = p_L.getLocX();
  int p_y = p_L.getLocY();

  if (abs(loc->getLocX() - p_x) <= 1 || abs(loc->getLocY() - p_y) <= 1){
    if (rand() % 2 == 1){
      player->hurt();
      cout << player->getName() << " got grabbed by " << name << " and got spooked! HP now at " << player->getHP() << endl;
    }
    else {
      cout << name << " reached out, but missed!\n";
    }
  }
}


ostream & operator<<(ostream & os, Skeleton &skeleton){
  os << "Skeleton ";
  os << skeleton.getName() << " "
     << skeleton.getHP() << " ";

     Location temp = skeleton.getLOC();
      int x = temp.getLocX();
      int y = temp.getLocY();
  os  << x << " " << y;
  return os;
}