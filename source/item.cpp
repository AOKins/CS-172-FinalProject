#include "item.h"

Item::Item(char set_type, bool set_traverse, Location* set_loc){
  type = set_type;
  traverse = set_traverse;
  loc = set_loc;
}

// Overloads the << operator for use in saving the game //
ostream & operator<<(ostream & os, Item &item){
  os << "Item "
     << item.getType() << " "
     << item.traversable() << " "
     << item.getLOC().getLocX() << " " 
     << item.getLOC().getLocY();
  return os;
}