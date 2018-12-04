///////////////////////////
// Program Name: FINAL PROJECT - BARE BONES 2
// Name: Andrew O'Kins
// Date: 11/20/2018
// Class and section: CS-172-1
////////////////////////////

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>

#include <cstdlib>
#include <ctime>
#include <typeinfo>

#include "player.h"
#include "skeleton.h"

using namespace std;

// Idea, no grid but rather a description that a skeleton is near and challenge is imagining the situation //




// Currently, simply makes an output text file and exits the program need to implement a system where it does the saving! //
void SaveGame(string num, vector<Entity*> list){
  ofstream savefile;
  savefile.open("save" + num + ".txt");
  for (int i = 0; i < list.size(); i++){
    // If the entity is the player, write as a player //
    if (typeid(Player) == typeid(*list[i])){
      cout << "writing player\n";
      Player* p1 = dynamic_cast<Player*>(list[i]);
      savefile << p1 << " ";}

    if (typeid(Skeleton) == typeid(*list[i])){
      cout << "writing skeleton\n";
      Skeleton* s = dynamic_cast<Skeleton*>(list[i]);
      savefile << s << " ";
    }
  }
  savefile.close();
  for (int i = 0; i < list.size(); i++){
    delete list[i];
  }
  cout << "Game Saved";
  exit(0);
}

void LoadGame(string name, vector<Entity*> entities){
  ifstream loadfile;
  loadfile.open( name + ".txt");
  if (loadfile.fail()){
    cout << "Failed to open load file!";
    exit(0);
  }
  string word;
  string load_name;
  bool load_key;
  int load_hp;
  int load_x, load_y;
  while(!loadfile.eof()){
    loadfile >> word;
    if (word == "Player"){
      // If the word is player, collect the data and push_back with a player entity //
      string load_name;
      loadfile >> load_name;
      loadfile >> load_hp;
      loadfile >> load_key;
      loadfile >> load_x >> load_y;
      entities.push_back(new Player(load_name, load_hp, load_x, load_y));
    }
    if (word == "Skeleton"){
      // If the word is player, collect the data and push_back with a player entity //
      string load_name;
      loadfile >> load_name;
      loadfile >> load_hp;
      loadfile >> load_x >> load_y;
      entities.push_back(new Skeleton(load_name, load_hp, load_x, load_y));
    }
  }
}


void NewGame(vector<Entity*> entities){
  // Create player into the vector (No load game feature yet) //
    string name;
    cout << "Input a name for your character\n";
    cin >> name;
    entities.push_back(new Player(name, 10, 0,0));

    entities.push_back(new Skeleton("Skeleton", 5, 1,1));

}


void PlayerTurn(int const p, vector<Entity*> entities){
      string command;
      string info;
      cout <<"Input command\n";
      cin >> command;
      cin >> info;
      if (command == "save"){
        SaveGame(info, entities);
      }

      if (command == "move"){   dynamic_cast<Player*>(entities[p])->move(info); }

      else if (command == "attack"){  dynamic_cast<Player*>(entities[p])->attack(); }

      else{ cout<< "Not a known command\n";}

}

// Player is always at location 0 in the vector, so make a constant //
int const p = 0;

int main() {

    vector<Entity*> entities;
    while (true){
    cout << "Load Game? y/n ";
    char confirm;
    if (confirm == 'y'){
      cout << "What is the name of your save? Don't include .txt\n";
      string saveName;
      cin >> saveName;
      LoadGame(saveName, entities);
      break;
    }
    else if (confirm == 'n'){
      NewGame(entities);
      break;
    }
    else {cout << "Not a correct response, type y or n\n";}
    }
    

    dynamic_cast<Player*>(entities[p])->attack();

    PlayerTurn(p, entities);

}