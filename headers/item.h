#ifndef _ITEM_H_
#define _ITEM_H_
#include <iostream>
#include "location.h"

class Item {
private:
  char type;
  bool traverse;
  Location* loc;
public:
  Item(char set_type, bool set_traverse, Location* set_loc);

  bool traversable() {return traverse;}
  char getType() {return type;}
  Location getLOC() {return *loc;}

};

ostream& operator<<(ostream & os, Item &item);

#endif