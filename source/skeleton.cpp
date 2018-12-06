#include "skeleton.h"
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <ctime>

void Skeleton::attack(Player* player){
  srand (time(NULL));

  if (abs(loc->getLocX() - player->getLOC().getLocX()) <= 1 || abs(loc->getLocY() - player->getLOC().getLocX()) <= 1){
    if (rand() % 2 == 1){
      player->hurt();
      cout << player->getName() << " got grabbed by " << name << " and got spooked! HP now at " << player->getHP() << endl;
    }
    else {
      cout << name << " reached out, but missed!\n";
    }
  }
  else {cout << name << "reach out, but was no where near!!\n";}
}


ostream & operator<<(ostream & os, Skeleton &skeleton){
  os << "Skeleton "
     << skeleton.getName() << " "
     << skeleton.getHP() << " "
     << skeleton.getLOC().getLocX() << " " 
     << skeleton.getLOC().getLocY();
  return os;
}