#include "skeleton.h"
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <ctime>

void Skeleton::attack(Player* player){
  srand (time(NULL));
  // if the distance in the x and y direction between the skeleton and the player is less than or equal to one, then it will attempt to "hurt" the player //
  if (abs(loc->getLocX() - player->getLOC().getLocX()) <= 1 && abs(loc->getLocY() - player->getLOC().getLocY()) <= 1){
    if (rand() % 2 == 1){
      player->hurt();
      cout << player->getName() << " got grabbed by " << name << " and got spooked! HP now at " << player->getHP() << endl;
    }
    else {
      cout << name << " reached out, but missed!\n";
    }
  }
}

bool Skeleton::CanMove(string direction, vector<Item*> items){
  // Go through all of the items, and if one of them is where the skeleton is trying to go to and it is not traversable, then can't move //
  for (int i = 0; i < items.size(); i++){
    if ( (targeting(direction, *loc) == items[i]->getLOC()) && !items[i]->traversable() ){
      return false;}
  }
  return true;
}

void Skeleton::move(string direction, vector<Item *> items){
    // If it can move in the normal direction, do it //
    if (CanMove(direction, items)) {
      if (direction == "north"){     loc->MoveUP();}
      else if (direction =="south"){ loc->MoveDOWN();}
      else if (direction == "west"){ loc->MoveLEFT();}
      else if (direction == "east"){ loc->MoveRIGHT();}
    }
    // If it can't, go to a direction that does work (not backwards though as it would only potentialy create a loop of forward and backward) //
    else if (!CanMove(direction,items)){
      // If the intended direction is northward //
      if (direction == "north"){
        if (CanMove("east", items)){
          loc->MoveRIGHT();
        }
        else if (CanMove("west", items)){
          loc->MoveLEFT();
        }

      }
      // If the intended direction is eastward //
      else if (direction == "east"){
        if (CanMove("north", items)) {
          loc->MoveUP();
        }
        else if (CanMove("south", items)) {
          loc->MoveDOWN();
        }
      }
      // If the intended direction is southward //
      else if (direction == "south"){
        if (CanMove("west", items)){
          loc->MoveLEFT();
        }
        else if (CanMove("east", items)){
          loc->MoveRIGHT();
        }
      }
      // If the intended directin is eastwad //
      else if (direction == "west"){
        if (CanMove("north", items)){
          loc->MoveUP();
        }
        else if (CanMove("south", items)){
          loc->MoveDOWN();
        }
      }
    }
    else {cout << name << " can't move there!\n";}
}

// Overloads the << operator for use in saving the game //
ostream & operator<<(ostream & os, Skeleton &skeleton){
  os << "Skeleton "
     << skeleton.getName() << " "
     << skeleton.getHP() << " "
     << skeleton.getLOC().getLocX() << " " 
     << skeleton.getLOC().getLocY();
  return os;
}