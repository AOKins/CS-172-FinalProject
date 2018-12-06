#include "location.h"
#include <iostream>

using namespace std;

Location::Location(){}

Location::Location(int start_x, int start_y){
    x = start_x;
    y = start_y;
}

int Location::getLocX(){
    return x;
}

int Location::getLocY(){
    return y;
}

void Location::MoveUP(){
    y += 1;
}
void Location::MoveDOWN(){
    y -= 1;
}
void Location::MoveLEFT(){
    x -= 1;
}
void Location::MoveRIGHT(){
    x += 1;
}

bool Location::operator==(Location other_loc) {
    if (y == other_loc.getLocY() && x == other_loc.getLocX()){
        return true;}
    else {return false;}
}


void Location::operator=(Location other_loc) {
    y = other_loc.getLocY();
    x = other_loc.getLocX();
}

ostream & operator<<(ostream & os, Location loc){
  os << "X: " << loc.getLocX() << endl;
  os << "Y: " << loc.getLocY() << endl;
  return os;
}