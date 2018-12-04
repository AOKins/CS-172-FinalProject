#include "skeleton.h"
#include <iostream>

void Skeleton::draw(){
  Entity::draw();
  cout << "P";
}

void Skeleton::move(string direction){

}

void Skeleton::attack(){

}


ostream & operator<<(ostream & os, Skeleton* &skeleton){
  os << "Skeleton ";
  os << skeleton->getName() << " "
     << skeleton->getHP() << " ";

     Location temp = skeleton->getLOC();
      int x = temp.getLocX();
      int y = temp.getLocY();
  os  << x << " " << y;
  return os;
}